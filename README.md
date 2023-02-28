# power-presenter
Combine data from inverter (rs232) and batteries (rs485) using on a arduino running on rust. Present the data on a small e-ink screen


## Hardware
* Inverter: Steca solarix pli 5000
* Batteries: Pylontech US2000C 
* RS485 -> TTL module (Max485)
* RJ45 to RS485 cable (custom pinout)
* RS232 -> TTL module (MAX3232)
* RJ45 to RS232 cable (custom pinout)
* E-ink display (https://www.waveshare.com/wiki/2.9inch_e-Paper_Module)
   * WaveShare 296x128 px
* Generic Arduino board
* 

## Software
* utilize pre build arduino crates from (https://github.com/atsamd-rs/atsamd/)

# Getting started

## Prerequisits
* rust
* arduino ide

## Build
1. cd to `rust-arduino-power`.
1. run `rustup target add atsamd21g` 
1. run `cargo build`

## Flash to Arduino (To be continued...)
