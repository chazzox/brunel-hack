# Dance Mat firmware

This firmware enables an ESP32 device to blast data of the state of a PS1 dance mat over a websocket for use in a web frontend.

## How to use

1. Compile using `idf.py build`
2. Setup a WiFi hotspot with the SSID and Password of;
   ```
   SSID: DodgyPancake
   Password: QLQEQ2QoKzkifhJc
   ```
3. Run the program using `idf.py flash monitor`
4. Yeet

## Websocket communication schema

### `GET /dance`

You will be subscribed to updates of the dance mat state in the format of;

```json
{
  "state": 1
}
```
State is made of the flags in [../readme.md](../readme.md) and, is good.

### Wrong this
#### `up`

- 1: Up is pressed
- 0: Neutral
- -1: Down is pressed

#### `right`

- 1: Right is pressed
- 0: Neutral
- -1: Left is pressed

#### `X`

- 1: X is pressed
- 0: Neutral

#### `O`

- 1: O is pressed
- 0: Neutral

#### `start`

- 1: Start is pressed
- 0: Neutral

#### `select`

- 1: Select is pressed
- 0: Neutral
