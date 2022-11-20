# uhhhhhhhhh

- to any future employers look no further, this is a terrible, terrible codebase
## HackBrunel V2 Submission

## canna get uhhhhh
> yes

## Data Format

### Buttons

| Button      | Bitshift | Decimal | Hexadecimal |
| ----------- | -------- | ------- | ----------- |
| START_DOWN  | 1 << 0   | 1       | 0x01        |
| SELECT_DOWN | 1 << 1   | 2       | 0x02        |
| X_DOWN      | 1 << 2   | 4       | 0x04        |
| O_DOWN      | 1 << 3   | 8       | 0x08        |
| UP_DOWN     | 1 << 4   | 16      | 0x10        |
| LEFT_DOWN   | 1 << 5   | 32      | 0x20        |
| RIGHT_DOWN  | 1 << 6   | 64      | 0x40        |
| DOWN_DOWN   | 1 << 7   | 128     | 0x80        |

### Highscore API

The highscore API accepts JSON body only.
Do not send `x-www-form-urlencoded` or `multipart/form-data`

#### POST `/score`

Take a picture of the winner and upload their score!

> Ejemplos
>
> ```json
> {
>   "name": "Danny Piper",
>   "score": 16300
> }
> ```
