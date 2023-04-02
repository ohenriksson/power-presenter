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

## Software
* utilize pre build arduino crates from (https://github.com/atsamd-rs/atsamd/)

# Getting started

## Prerequisits
* rust
* arduino ide
* Cargo installed (see https://rustup.rs)
* Rust nightly compilers version installed.

## Installation and setup
Installation and setup is performed following the steps below copied from [LogRockets blog](https://blog.logrocket.com/complete-guide-running-rust-arduino/)

### Using Avrdude
A Hardware Abstraction Layer (HAL) is required to run Rust on AVR microcontrollers and other common boards. To get this, you need the nightly Rust compiler that compiles Rust code to AVR on your machine. Run the command below to install it:

```bash
rustup toolchain install nightly
```

### On Windows
On Windows, you will need to install Scoop via Powershell using the command:
```bash
Set-ExecutionPolicy RemoteSigned -Scope CurrentUser # Needed to run a remote script the first time
irm get.scoop.sh | iex 
```

When this has been performed use the following commands to install avr-gcc and avrdude:
```bash
scoop install avr-gcc
```
```bash
scoop install avrdude
```

There is an [installation guide](https://docs.rust-embedded.org/book/intro/install.html) for all operating systems, should you encounter any obstacles following the guide.

After all the steps above is completed, it's time to install the [ravedudetool](https://github.com/Rahix/avr-hal/tree/main/ravedude) for flashing the microcontroller board against **cargo**

This tool handles everything from finding the board, flashing the board, and listening to connections. You simply have to run the **cargo run** command.

```bash
cargo +stable install ravedude
```

### On macOS
Follow the steps provided on [LogRockets blog](https://blog.logrocket.com/complete-guide-running-rust-arduino/)

### On Linux
Follow the steps provided on [LogRockets blog](https://blog.logrocket.com/complete-guide-running-rust-arduino/)

## Setting up the project

### Setting up config.toml
#### **Build**  - Set the path to ./avr-specs/*yourArduinoModel.json* - Example below
[build]
target = "avr-specs/avr-atmega328p.json"

#### **Setting Target** - Runner should be set to "ravedude nano -cb *baud* -P *COM-portnumber* for the USB where the arduino is connected.
[target.'cfg(target_arch = "avr")']

runner = "ravedude nano -cb 57600 -P COM4"

#### Setting unstable
[unstable]

build-std = ["core"]

### Checking the dependencies
If there is an error in installing the **libudev-sys** crate, you will have to include it in youe cargo.toml file under dependencies.

The libudev Rust binding is a crate that provides declarations and linkage for the libudev C library. It is Linux-specific, so it is **not available for Windows or OSX operating systems**.

```bash
[dependencies]
libudev-sys = "0.1"
```

Alternatively, you can run the command below to install the libudev-sys crate:

```bash
sudo apt-get install libudev-dev
```

You can consult the [libudev-sys](https://github.com/dcuddeback/libudev-sys) repository in case of further issues arising from pkg-config.


## Build
1. cd to `rust-arduino-power`.
1. run `cargo build`
   * It takes a while, since it is a CPU-intensive task. Afterward, you will find a **.elf** file under **target/avr-atmega328p/debug/**. To run your own program, you can edit the **main.rs**

Below is an example of the basic LED blinking program:

      #![no_std]
      #![no_main]

      use panic_halt as _;

      #[arduino_hal::entry]
      fn main() -> ! {
         let dp = arduino_hal::Peripherals::take().unwrap();
         let pins = arduino_hal::pins!(dp);

         let mut led = pins.d13.into_output();

         loop {
            led.toggle();
            arduino_hal::delay_ms(1000);
         }
      }


## Flash to Arduino
```bash
cargo run
```