# Smarte modulare Stromversorgung

<details>
<summaryIdee und Ziel</summary>

Dieses Projekt ist als proof-of-concept der Bachelorthesis entstanden: <br> <i>Entwurf einer quelloffenen, smarten, modularen Stromversorgung zur Verwendung im ioBroker</i>

Das Ziel ist es, ein modulares System zu erstellen, mit dem unterschiedliche Arten von Geräten mit Strom versorgt werden können. Dabei können Module je nach Bedarf frei mit Aktoren und Sensoren ausgestattet werden. Mehrere solcher Module können kombiniert und mit einem sogenannten Kopf zu einem System zusammengesetzt werden. Durch den Kopf werden die Module mit Strom versorgt, sowohl mit Kleinspannung um die Platine und Peripherie des Moduls zu betreiben als auch mit der vollen 230V Niederspannung zur Versorgung der angeschlossenen Abnehmer. Ebenfalls stellt der Kopf eine Verbindung zu einem smart-home-System wie dem [ioBroker](https://www.iobroker.net/?lang=de) her, durch Verwendung von Industrieüblichen Protokollen und Standards wie MQTT und WLAN/ZigBee soll die Einbindung in die meisten selbstgehosteten Systeme (z.B. HomeAssistant oder FHEM) möglich sein.

</details>


<details>
<summary>Aufbau Hardware</summary>
<br><br>
Zwei beispielhafte Systeme sind diese:

1. Zum Einsatz z.B. auf dem Schreibtisch im Arbeitszimmer.<br>
	![beispielhaftes System für den Schreibtisch](/renderings/composite1-desk.png?raw=true)
	<br>
	Es besteht (v.l.n.r.) aus 
	* einem Kopf
	* einem Modul mit zwei Steckdosen des Typs F, mit jeweils
		* einer LED als Zustandsanzeige
		* einem Taster zum direkten schalten
		* optional auch Ammetern zur Überwachung des Energieverbrauchs
	* einem Modul mit vier Tastern zum Steuern anderer Geräte
	* einem Modul mit einer dimmbaren Steckdose des Typs F, die
		* einen Drehgeber (Rotary encoder) zum direkten Dimmen und Schalten besitzt
		* optional kann wieder ein Ammeter verbaut werden
	* einem Endmodul mit Temperatursensor

2. Kann z.B. auf der anderen Seite des Arbeitszimmers positioniert werden.<br>
![beispielhaftes System für den Boden](/renderings/composite2-floor.png?raw=true)<br>
	Es besteht (v.l.n.r.) aus 
	* einem Kopf
	* einem Modul mit zwei Steckdosen des Typs F, mit jeweils
		* einer LED als Zustandsanzeige
		* einem Taster zum direkten schalten
		* optional auch Ammetern zur Überwachung des Energieverbrauchs
	* einem Modul mit zwei nur extern steuerbaren Steckdosen des Typs F (wieder optional mit Ammeter)
	* einem passiven Endmodul
<br>

In dieser Kombination kann am Schreibtisch ein PC mit Monitor angeschlossen und deren Stromversorgung direkt gesteuert werden. Eine Tischlampe mit passendem Leuchmittel kann angeschlossen und direkt über das Modul gedimmt werden.<br>
Am zweiten System kann z.B. ein Deckenfluter und ein Fernseher am ersten Modul angeschlossen werden, so dass diese direkt dort geschaltet werden können. Am zweiten Modul können Drucker und NAS angeschlossen werden, die nur selten geschaltet werden. Durch das entsprechende Modul im System am Schreibtisch können alle hier angesteckten Geräte auch bequem von dort aus geschaltet werden.<br>
Da all dies in einem smart-home-System eingebunden ist, lassen sich alle Geräte auch extern steuern und die Temberatur (letztes Modul am Schreibtisch) kann eingelesen und anderweitig verwendet werden.

</details>


<details>
<summary>Aufbau Software</summary>
<br><br>
graph

</details>

