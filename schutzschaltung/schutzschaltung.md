# Dokumentation: Schutzschaltung gegen Tiefentladung (18650 Li-Ion)

**Projekt:** Autonom Driving Car  
**Bauteil:** Akku-Schutzschaltung (Under-Voltage Lockout - UVLO)

---

## a) Berechnung der Abschaltspannung

Das Akkupaket besteht aus zwei 18650 Lithium-Ionen-Zellen, die in Reihe geschaltet sind (2S-Konfiguration). 
* **Nennspannung pro Zelle:** 3,7 V
* **Nennspannung Gesamtpaket:** 2 × 3,7 V = 7,4 V
* **Kritische Mindestspannung pro Zelle:** 3,0 V

Die notwendige **Abschaltspannung für das Gesamtpaket** berechnet sich somit aus:  
**2 × 3,0 V = 6,0 V**

Sobald die Gesamtspannung des Akkupakets auf 6,0 V abfällt, muss die Schaltung den Stromfluss zum Verbraucher zwingend unterbrechen.

---

## b) Schaltungskonzept (Blockschaltbild & Aufbau)



Für diese Schaltung verwenden wir einen **Komparator** (z. B. LM393 oder einen als Komparator genutzten Operationsverstärker), eine **Z-Diode** als Referenz, einen **Spannungsteiler** und einen **P-Kanal MOSFET** als elektronischen Schalter.

**Kernkomponenten:**
1. **Referenzspannungsquelle:** Eine Z-Diode (z. B. 3,3 V) mit Vorwiderstand erzeugt eine konstante Vergleichsspannung.
2. **Spannungsteiler:** Zwei Widerstände (R1 und R2) teilen die aktuelle Akkuspannung so herunter, dass sie mit der Referenzspannung verglichen werden kann.
3. **Komparator (Das Gehirn):** Vergleicht die geteilte Akkuspannung mit der Referenzspannung der Z-Diode.
4. **Schalt-MOSFET (Die Muskeln):** Ein P-Kanal MOSFET, der in der Plus-Leitung (High-Side) zum Verbraucher sitzt und den Stromkreis öffnet oder schließt.

---

## c) Funktionsweise der Schaltung

Die Schaltung funktioniert nach einem simplen "Waagen-Prinzip":

1. **Die konstante Seite:** Die Z-Diode erzeugt am nicht-invertierenden Eingang (`+`) des Komparators eine felsenfeine Spannung (z.B. exakt 3,3 V), völlig unabhängig davon, wie voll der Akku gerade ist.
2. **Die variable Seite:** Der Spannungsteiler misst die aktuelle Akkuspannung und gibt einen proportionalen Teil davon an den invertierenden Eingang (`-`) des Komparators. Wir dimensionieren die Widerstände so, dass bei exakt 6,0 V Akkuspannung am Eingang des Komparators genau 3,3 V anliegen.
3. **Der Vergleich:** * **Akku voll (> 6,0 V):** Die Spannung am `-` Eingang ist *größer* als am `+` Eingang. Der Ausgang des Komparators schaltet auf LOW (GND). Dadurch wird das Gate des P-Kanal MOSFETs auf ein niedriges Potenzial gezogen, der MOSFET leitet, und das Auto hat Strom.
   * **Akku leer (< 6,0 V):** Die Spannung am `-` Eingang fällt *unter* die 3,3 V des `+` Eingangs. Der Komparator kippt um und schaltet seinen Ausgang auf HIGH (Akkuspannung). Das Gate des MOSFETs hat nun keine Spannungsdifferenz mehr zur Source, der MOSFET sperrt sofort – das Auto ist stromlos und der Akku gerettet.
4. **Hysterese (Wichtig!):** Damit die Schaltung bei genau 6,0 V nicht wild an- und ausschaltet (weil die Akkuspannung ohne Last kurzzeitig wieder minimal ansteigt), wird ein hochohmiger Widerstand vom Ausgang des Komparators zurück zum `+` Eingang geschaltet. Das sorgt dafür, dass die Schaltung bei 6,0 V abschaltet, aber erst wieder bei z.B. 6,5 V freigibt, wenn der Akku geladen wurde.

---

## d) Warum ist eine Tiefentladung für Li-Ion-Akkus gefährlich?

Lithium-Ionen-Akkus reagieren auf Tiefentladung (Spannung unter ca. 2,5 V - 3,0 V) hochsensibel und nehmen irreversiblen Schaden. Dafür gibt es vor allem chemische Gründe:

* **Kupferauflösung:** Die Anode (Minuspol) besteht bei Li-Ion-Zellen oft aus einer Kupferfolie. Fällt die Spannung zu tief, beginnt sich das Kupfer im Elektrolyten aufzulösen. 
* **Kurzschlussgefahr beim Laden:** Wird ein tiefentladener Akku wieder aufgeladen, lagern sich diese gelösten Kupferionen als spitze Nadeln (Dendriten) ab. Diese können die hauchdünne Trennschicht (Separator) im Akku durchstechen und einen internen Kurzschluss verursachen.
* **Brand- und Explosionsgefahr:** Ein solcher interner Kurzschluss führt zu extremen Temperaturen (Thermal Runaway). Der Akku kann sich aufblähen, ausgasen oder sogar explosionsartig in Brand geraten.
* **Kapazitätsverlust:** Selbst wenn es nicht zum Schlimmsten kommt, zersetzt sich bei Tiefentladung der Elektrolyt, was zu einem sofortigen und dauerhaften Verlust der Speicherkapazität führt.

---

## e) Aufbau und Test (Praxis)

*(Dieser Teil wird nach dem Labortermin im Wiki mit Fotos ergänzt)*

**Geplantes Test-Szenario für das Steckbrett:**
1. Statt der Akkus wird zunächst ein **Labornetzteil** an den Eingang der Schaltung angeschlossen, um die Spannung sicher simulieren zu können.
2. An den Ausgang wird eine LED mit Vorwiderstand (als Verbraucher-Dummy) angeschlossen.
3. Die Spannung am Netzteil wird langsam von 8,4 V (Akku voll) heruntergeregelt.
4. Es wird am Multimeter verifiziert, dass die LED bei exakt **6,0 V** erlischt.
5. Anschließend wird die Spannung wieder erhöht, um die Hysterese zu testen (LED sollte erst bei > 6,2 V wieder angehen).
6. Nach erfolgreichem Test wird die Schaltung zwischen die echten 18650-Akkus und die Motor-Treiber des Autos integriert.
