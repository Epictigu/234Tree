# 234Tree
[![Latest Release](https://img.shields.io/github/release/Epictigu/234Tree?label=Download)](https://github.com/Epictigu/234Tree/releases/)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

<dd>Dieses Programm wurde zur Darstellung von Bäumen erstellt.</dd>
<dd>Im Moment unterstützt unser Programm die Darstellung von:</dd>

+ Gewöhnliche Bäume
+ 234-Bäume
+ Rot-Schwarz-Bäume

<dd>Die einzelnen Darstellungsfunktionen sind statische Funktionen der "ShowKnot"-Klasse.</dd>
<dd>Mit Verfügbarkeit des Projektes ist es also möglich die display-Methode zusammen mit dem dazugehörigen Baum aufzurufen</dd>
<dd>um ein Fenster mit der gewünschten Anzeige darzustellen.</dd>

### Wichtig!
<dd>Es ist allerdings zu beachten, dass eine leicht veränderte Version der Baumklassen genutzt wurde.</dd>
<dd>In dem Original fehlten einige Getter Methoden, was eine Darstellung schlichtweg unmöglich gemacht hat.</dd>
<dd>Um die Bäume also zu benutzen müsste das Include zu den projektinternen Baumklassen einmal umgeändert werden,</dd>
<dd>sonst sollte aber alles ohne weitere Änderungen funktionieren.</dd>

## Implementation
<dd>Generell bieten einige IDEs eine Implementation von Qt an.</dd>
<dd>Dies wird zumeist durch dafür entwickelte Plugins realisiert.</dd>
<dd>Diese sind allerdings zumeist sehr veraltet und nicht mehr unterstützt.</dd>

<dd>Aus diesem Grund empfehlen wir die Nutzung des QtCreator,</dd>
<dd>mit dem der gegebene Code auch entwickelt wurde.</dd>

<dd>Bei einer sowieso benötigten <a href="http://www.qt.io/download-open-source">Installation von Qt</a> (was mehrere Stunden dauern kann),</dd>
<dd>wird auch normalerweise QtCreator schon mit installiert.</dd>



## Testprogramm
<dd>Das mitgelieferte Beispielprogramm ist standardmäßig auf die Darstellung eines 234-Baums eingestellt.</dd>
<dd>Über die Nutzung von Kommandozeilenparameter lassen sich dabei noch einige Details einstellen.</dd>
<dd>Eine <0-2> am Anfang der Parameter ändert beispielsweise den Typ des Baumes um.</dd>
<dd>(0 = Gewöhnlich, 1= 234-Baum, 2 = Rot-Schwarz-Baum)</dd>

<dd>Ansonsten gelten für den Gewöhnliche Bäume die gleichen Parameter wie im <a href="https://github.com/Epictigu/QTTree">letzten Projekt</a>.<dd>
