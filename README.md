# Example Pebble watch weather app in C/JS.

Just an example weather app for the pebble watch. To build you will need the
Pebble SDK 4.1.0+ and either the pebble watch or the qemu pebble watch
emulator. Then from the root directory you would run:

```
$ pebble build
$ pebble install
```

or for emulation without a phone:

```
$ pebble build
$ pebble install --emulator diorite
```

Note this app is written for the diorite target (Pebble 2), older Pebble support
like original Pebble or Pebble Time is not supported.