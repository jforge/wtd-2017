# wtd-2017
Team R.E.D. Ressourcen für den What The Data!? Hackathon 2017

[patch-pattern]: https://github.com/jforge/wtd-2017/raw/master/docs/images/RED-logo.png "Team RED Logo"

## R.E.D. Request Patch

Jessica Broscheit, Markus Ulsaß und Klaus Pittig sind ein interdisziplinäres Team
aus Designerin, Hardware-Entwickler und Softwareentwickler.

In dem Projekt R.E.D. – Request Patch wurde sich der Aufgabe gestellt, an der
Schnittstelle Smart Environments und Human Computer Interaction zu arbeiten,

um ein neuartiges, intuitives und proaktives User Interface (UI) für Smart
Environments zu entwickeln, in dem individuelle und konfigurierbare Services
auf der UI definiert werden können.

Als Use Case wurde sich einem Request System gewidmet, in dem der Nutzer,
ein CO2 Grenzwert der Methanisierung, über ein Patch angezeigt bekommt.

Ziel war es nicht nur eine effiziente Kommunikationsstruktur zu entwickeln,
sondern die Informationen auch ästhetisch und intuitiv zu übermitteln.

Das heißt es sollten keine blickenden RGB LEDs verbaut werden
(kein Wearable Weihnachtsbaum), sondern "Smart Textiles" genutzt werden.




## Idee und Lösung

### Hardware

- Thermochromatische Farbe gesteuert durch leitfähiges Garn.
- Kupferfolie für kapazitive Sensorik
- Wemos D1 mini ESP-8266

### Software:

- Arduino Sketch für Wifi, MQTT Client und Hardwaresteuerung
- Node RED Flow für Signalsteuerung und Alarmierung


## Ausblick

- Grenzwert Analyse,
- Materialstudie mit Thermochromatischen Filament.
- Außerdem wäre eine Nutzung am Flughafen, Krankenhaus oder Reiseführer vorstellbar.

## Quellen

- Wolter & Kirsch: Smart Environments: What is it and Why should we care?
KI – Künstliche Intelligenz, August 2017, http://link.springer.com/article/10.1007/s13218-017-0498-4
- Weiser: The World is not a Desktop, Interaction, Januar 1994, http://dl.acm.org/citation.cfm?id=174801
- Weiser & Brown: Das kommende Zeitalter der Calm Technology, Internet der Dinge, Transcript Verlag

## Weitere Ressourcen

- Related gist: https://gist.github.com/jforge/483b57081a64f4204c507bb75a6ec35f
- Vorlage für den thermochromatischen Stoff

![alt text][patch-pattern]

[patch-pattern]: https://github.com/jforge/wtd-2017/raw/master/docs/images/patch-pattern-thermochromic-yarn.png "Patch Pattern"
