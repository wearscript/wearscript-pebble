# Wearscript Pebble
#### Forked from meiguro/simplyjs

* [wearscript-pebble api docs](http://www.wearscript.com/en/latest/pebble.html)

### Installation insttructions
* Binary install
    * Copy wearscript-pebble-[version].pbw from release/ folder to device (e.g. dropbox, drive, adb)
    * Download to device, and open .pbw file.

* Building from source
    * Prerequisites
        [Pebble Getting Started](https://developer.getpebble.com/2/getting-started/)
        * Install Pebble SDK
        * Install latest Pebble firmware (current 2.0.2)
        * Install 2.0 BETA Android App
    
    * Build client
        * Build pebble app from top level directory
        ```
        pebble build
        ```
        * Send to pebble
        ```
        pebble install --phone [ip address]
        ```
