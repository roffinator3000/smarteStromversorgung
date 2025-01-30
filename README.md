# Smarte modulare Stromversorgung


Dieses Projekt ist als proof-of-concept der Bachelorthesis entstanden: <br> <i>Entwurf einer quelloffenen, smarten, modularen Stromversorgung zur Verwendung im ioBroker</i>

Das Ziel ist es, ein modulares System zu erstellen, mit dem unterschiedliche Arten von Geräten mit Strom versorg werden können. Dabei können Module je nach Bedarf frei mit Aktoren und Sensoren ausgestattet werden. Mehrere solcher Module können kombiniert und mit einem sogenannten Kopf zu einem System zusammengesetzt werden. Durch den Kopf werden die Module mit Strom versorgt, sowohl mit Kleinspannung um die Platine und Peripherie des Moduls zu betreiben als auch mit der vollen 230V Niederspannung zur Versorgung der angeschlossenen Abnehmer. Ebenfalls stellt der Kopf eine Verbindung zu einem smart-home-System wie dem [ioBroker](https://www.iobroker.net/?lang=de) her, durch Verwendung von Industrieüblichen Protokollen und Standards wie MQTT und WLAN/ZigBee soll die Einbindung in die meisten selbstgehosteten Systeme (z.B. HomeAssistant oder FHEM) möglich sein
