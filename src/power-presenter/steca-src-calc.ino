unsigned int cal_crc_half(byte command[] , byte len)
{
    unsigned int crc_ta[16] =
        {/* CRC 余式表 */
         0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7,
         0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef};

    byte *pin = command;
    unsigned int crc;
    byte da;
    byte *ptr;
    byte bCRCHign;
    byte bCRCLow;

    ptr = pin;
    crc = 0;
    len--;
    while (len-- != 0)
    {
        da = ((byte)(crc >> 8)) >> 4;   /*暂存 CRC 的高四位 */
        crc <<= 4;                       /* CRC 右移 4 位,相当于取 CRC 的低 12 位)*/
        crc ^= crc_ta[da ^ (*ptr >> 4)]; /* CRC 的高 4 位和本字节的前半字节相加后查表计算 CRC, 然后加上上一次 CRC 的余数 */

        da = ((byte)(crc >> 8)) >> 4;     /*暂存 CRC 的高 4 位 */
        crc <<= 4;                         /* CRC 右移 4 位, 相当于 CRC 的低 12 位) */
        crc ^= crc_ta[da ^ (*ptr & 0x0f)]; /* CRC 的高 4 位和本字节的后半字节相加后查表计算 CRC,然后再加上上一次 CRC 的余数 */

        ptr++;
    }
    bCRCLow = crc;
    bCRCHign = (byte)(crc >> 8);
    if (bCRCLow == 0x28 || bCRCLow == 0x0d || bCRCLow == 0x0a)
    {
        bCRCLow++;
    }
    if (bCRCHign == 0x28 || bCRCHign == 0x0d || bCRCHign == 0x0a)
    {
        bCRCHign++;
    }
    crc = ((unsigned int)bCRCHign) << 8;
    crc += bCRCLow;
    return (crc);
}