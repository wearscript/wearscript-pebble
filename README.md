# Wearscript Pebble
#### Forked from meiguro/simplyjs

* [wearscript-pebble api docs](http://www.wearscript.com/en/latest/pebble.html)

## Installation instructions
### Prerequisites
* Install Pebble android application.
* Install latest Pebble firmware (current 2.0.2)

### Binary install
* Grab latest release from github releases tab.
* Download to device, and open .pbw file.

### Building from source
* Prerequisites [Pebble Getting Started](https://developer.getpebble.com/2/getting-started/)
    * Install the Pebble SDK
    * Install Pebble ARM toolchain.     

    * Build client
        * Build pebble app from top level directory
        ```
        pebble build
        ```
        * Send to pebble
        ```
        pebble install --phone [ip address]
        ```
