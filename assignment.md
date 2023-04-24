Prostřednictvím vedoucího si zapůjčte 1 ks platformy FITkit 3 a přípravek Maticový displej. Termín možnosti zapůjčení vám vedoucí oznámí emailem. Seznamte se s principem tvorby vestavných aplikací založených na mikrokontroléru Kinetis K60 (s jádrem ARM Cortex-M4) fy NXP s využitím vývojového prostředí Kinetis Design Studio (KDS) nebo MCUXpresso.

Cílem tohoto projektu je vytvořit zjednodušenou implementaci hry HAD na platformě FitKit3.

Zájemci/kyně o řešení projektu na jiném technickém vybavení (např. FITkit 1.2/1.3, Arduino, ESP32, Raspberry Pi, Zynq; toto vybavení je nutno opatřit si bez pomoci vedoucího, např. v knihovně FIT) zkonzultují toto vybavení s vedoucím a řešit začnou až s jeho souhlasem. Nemáte-li odsouhlaseno jiné technické vybavení, předpokládá se řešení na platformě FITkit 3, kterou si za tímto účelem včas zapůjčíte u vedoucího projektu.

Upřesnění požadavků na implementaci:

Had bude mít pouze pevnou délku, nebude se zobrazovat žádné "ovoce". Bude se tedy pouze "procházet" po dostupné zobrazovací ploše.
Zobrazování na maticovém displeji bude řešeno pomocí tzv. multiplexingu. Nahlédněte do dokumentace (bude přidán odkaz), jakým způsobem se displej ovládá (sloupce se volí jako číslo 0-15 (4 bity) a číslo 0-255 pro řádky (8 bitů) volí, které diody budou ve vybraném řádku svítit.
Pokuste se v co největší míře využít vestavěných součástí či periferních modulů mikrokontroleru - zejména modulu časovače pro obsluhu displeje.
Dokumentace, odevzdání a hodnocení projektu:

Vytvořte přehlednou dokumentaci k přípravě, způsobu realizace, k funkčnosti a vlastnostem řešení projektu.
Řešení (projekt, bez binárních souborů sestavitelných na základě zdrojových souborů v projektu, a dokumentaci ve zdrojové i binární, tj. PDF, podobě)odevzdávejte prostřednictvím IS v jediném ZIP archívu.
Předvedení řešení se implicitně předpokládá v osobní podobě, s následným vrácením zapůjčeného vybavení. Pokud by, vzhledem k pandemickým či jiným okolnostem daným "vyšší mocí", osobní předvedení/vrácení nebylo možné, připravte se prosím na náhradní možnost - např. online/vzdálené předvedení přes Microsoft Teams, Google Meet apod., tvorbu krátkého videa demonstrujícího řešení, vrácení vybavení na vrátnici, u příležitosti zkoušky apod.
Hodnocení projektu bude provedeno na základě ohodnocení složek E, F, Q, P, D z hodnoticího klíče. Po dokončení projektu využijte tento klíč k autoevaluaci složek E, F, Q, P, D a výsledného bodového hodnocení (výsledek autoevaluace umístěte např. na konec dokumentace k projektu) - poskytnete mi tak cennou zpětnou vazbu a informaci o Vámi očekávaném hodnocení projektu.
