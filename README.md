### Описание

Функция parse_4D42_block предназначена для чтения и парсинга бинарного файла. 
Она ищет определённые блоки данных, обозначенные сигнатурой "MB" (4D42 в шестнадцатеричном формате), и извлекает информацию о целях, выводя её в десятичном формате.

### Пример вывода

```
The 4D42 (MB) block was found, length=5123.
Id 86:
  Vertical distance: 1433.8 m
  Lateral distance: 4300.7 m
  Speed (y direction): 5324.7 m/s
  Target type: 0
  Lane number: 1
  Front spacing: 1638.9 m
  Front time interval: 2457.7 s
  Speed (x direction): 0 m/s
  Heading angle: 36166
  Incidents: 0
  Radar X: 2.81857e+08 m
  Radar Y: 9.39655e+07 m
  Blind Mark: 0
  Car length: 4.5 m
  Car width: 1.8 m
----------------------------------------
```

### Лицензия

Этот проект распространяется по лицензии BSD-3-Clause license.
