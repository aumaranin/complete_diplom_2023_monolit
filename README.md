# Выпускная квалификационная работа магистра 2023
<p> 
Экспертная система обнаружения нарушений техники безопасности методом анализа видеопотока
</p>
<p> 
Университет: МГТУ им. Баумана
</p>
<p> 
Кафедра: ИУ6 (Компьютерные системы и сети)
</p>
<p> 
Выполнил: Маранин Александ Юрьевич
</p>

## Описание
Система состоит из двух модулей: 
<ol>
<li>модуля накопления зананий, с помощью которого эксперт по технике безопасности работает с конфигурациями: размечает зоны и линии, добавляет шаблоны сопоставляемых объектов, добавляет источники видеопотока (IP-камеры, USB-камеры, видеозаписи), добавляет правила сопоставления зон и правил с учетом свойств.</li>
<li>модуля наблюдателя, который отображает все видеопотоки, подключенные к системе, может отобразить детальную информацию по видеопотоку с отрисованными зонами и распознанными объектами (основные объекты - синей рамкой, второстепенные объекты, такие как средства индивидуальной защиты (каски, жилеты) - белой), а также отобразить журнал с тревожными ситуациями
</li>
</ol>

## Модуль классификации
<p>
Основным алгоритмом является алгоритм распознавания YOLOv5. На его основе создан алгоритм, использующий две модели нейросети: первая модель - обычная yolov5n.onnx, обученная на наборе данных Microsoft COCO, способная определять 80 классов. Вторая модель - узкоспециализированная, обученная на специально собранном наборе данных для распознавания средств индивидуальной защиты. После обнаружения основных объектов и второстепенных, они сопоставляются по месторасположению и создаются сложные-составные объекты.
</p>
## Модель знаний
<p>Система использует декларативные знаний (зоны и обнаруженные объекты) и процедурные знания (правила сопоставления). Правила сравнивают секторы зоны и основных объектов, проверяют соотвествие класса и наличие требуемых свойств.<br>
Если секторы месторасположения пересекаются, класс - совпадает, а у объекта каких-то свойств нехватает (например, отсутствует каска или жилет) - срабатывает правила и реакции системы, заданные экспертом.</p>

## Реакции системы
<p>
В системе заложены 4 реакции системы на сработанные правила:
<ul>
<li>оповежение оператора,
<li>запись в базу данных,
<li>сохранение кадра,
<li>выполнение произвольного bash-скрипта. Возможность выполнения bash-скрипта расширяет реакции системы многократно. Система может скачать какое-то приложение через утилиту wget и запустить процесс, или отправить http-запрос в интернет утилитой curl.
</p>