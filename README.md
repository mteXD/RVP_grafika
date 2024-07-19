# RVP_grafika

## Povzetek

Pričujoče delo opisuje sestavo grafičnega sklada na operacijskem sistemu Linux.
Opisuje posplošen model grafičnih skladov, nekaj osnov grafične strojne opreme -
medpomnilnika okvirjev (angl. *framebuffer device*), grafične procesne enote (GPE)
in grafičnih kartic - in pa posamezne komponente ter najpogostejše aplikacije,
ki jih zasledimo na Linuxovih sistemih. To so (poleg jedra in gonilnikov) grafični API
(OpenGL z implementacijo Mesa), podsistema DRM in infrastruktura DRI, okenski sistemi in
prikazni strežniki (okenski sistem X in Wayland Compositor), kompozitor in ostala
višjenivojska grafična orodja.

Cilj je približati osnove grafičnega programiranja na Linuxu začetnikom na tem
področju. Za razumevanje spodnjih konceptov je potrebno razumeti le nekaj osnov
delovanja in organizacije računalniških sistemov ter delovanja Linux operacijskega sistema 
(npr. sistemski klici). Navedeni primeri so napisani v jeziku C.

Pričujoče delo ***se ne poglablja*** v matematiko, ki opisuje računalniško 
grafiko. Prav tako delo ni priročnik za uporabo katerekoli navedene knjižnice; tu ni opisov,
katere funkcije in strukture sestavljajo OpenGL, okenski sistem X ali podsisteme Linux
jedra, niti ni navodil za uporabo visokonivojskih orodij, kot je GTK+. Pričujoče delo
zgolj daje izhodišče za začetnika, ta pa se lahko po svojih željah nato poglobi v
posamezne dele grafičnega sklada.

## Prevajanje

Priporočeno je imeti naložen paket `texlive` v celoti (tj. z vsemi knjižnicami).

Za prevajanje:

Ukaz po spreminjanju datoteke `linux_grafika.tex`: 
```bash
lualatex --shell-escape linux_grafika.tex
```

Ukazi po spreminjanju datoteke `refs.bib` (citati):
```bash
lualatex --shell-escape linux_grafika.tex
bibtex linux_grafika
lualatex --shell-escape linux_grafika.tex
lualatex --shell-escape linux_grafika.tex
```

Te štiri vrstice so zapisane v datoteki `compile.sh`, ki ga je možno pognati namesto teh ukazov.
