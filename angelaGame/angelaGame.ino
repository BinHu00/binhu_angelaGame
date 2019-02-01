int meta;
int dado[7] = {8, 1, 2, 3, 4, 5, 6};
int turno = -1;
int dadoGiocato;
int punteggio = 0;

void setup() {
  Serial.begin(9600);
}


void loop() {
  if (turno == -1) {
    Serial.println("Inserisci la meta, valore da 30 a 100.");
    sceltaMeta();
    Serial.println("META = " + String(meta) + ", il valore 0 viene inserito usando il tasto 8 della tastiera, turno G1");
    turno = 0;
  } else {
    if (turno % 2 == 0) {
      giocataDado();
    } else {
      giocataDado();
    }
  }
}

void vuoto() {
  for (int i = 0; i < 5; i++) {
    Serial.println("");
  }
}

void cambiaTurno() {
  vuoto();
  if (turno == 0) {
    turno = 1;
    Serial.println("Turno G2");
  } else {
    turno = 0;
    Serial.println("Turno G1");
  }
}

void resetPartita() {
  resetDadi();
  turno = -1;
  meta = 0;
  dado[0] = 8;
}

bool controlloVittoria() {
  if (punteggio == meta) {
    if (turno == 0) {
      Serial.println("Meta raggiunta, ha vinto G1");
    } else {
      Serial.println("Meta raggiunta, ha vinto G2");
    }
    resetPartita();
    return true;
  } else if (punteggio > meta) {
    if (turno == 0) {
      Serial.println("Meta Superata, ha vinto G2");
    } else {
      Serial.println("Meta Superata, Ha vinto G1");
    }
    resetPartita();
    return true;
  }
  return false;
}

void sceltaMeta() {
  while (Serial.available() == 0 && meta == 0)
  {
    meta = Serial.parseInt();
    if (meta != 0) {
      if (meta < 30 || meta > 100) {
        Serial.println("Meta " + String(meta) + " non valida, inserire valore da 30 a 100.");
        meta = 0;
      }
    }
  }
  vuoto();
}

void giocataDado() {
  sceltaDado();
  if (dadoValido(dadoGiocato)) {
    resetDadi();
    cambiaDadiGiocabili(dadoGiocato);
    if (dadoGiocato != 8) {
      punteggio += dadoGiocato;
    }
    Serial.println("Punteggio = " + String(punteggio));
    if (controlloVittoria() == false) {
      cambiaTurno();
    }
  } else {
    Serial.println("Dado non valido, reinserire valore.");
  }
  dadoGiocato = 0;
}

void sceltaDado() {
  Serial.println("Inserisci valore dado");
  while (Serial.available() == 0 && dadoGiocato == 0) {
    dadoGiocato = Serial.parseInt();
  }
  Serial.println("DADO = " + String(dadoGiocato));
}

bool dadoValido(int dadoGiocato) {
  for (int i = 0; i < 7; i++) {
    if (dado[i] == dadoGiocato) {
      return true;
    }
  }
  return false;
}

void cambiaDadiGiocabili(int dadoGiocato) {
  if (dadoGiocato == 0) {
    cambiaValoreDado(0);
  }
  if (dadoGiocato == 1 || dadoGiocato == 6) {
    cambiaValoreDado(1);
    cambiaValoreDado(6);
  }
  if (dadoGiocato == 2 || dadoGiocato == 5) {
    cambiaValoreDado(2);
    cambiaValoreDado(5);
  }
  if (dadoGiocato == 3 || dadoGiocato == 4) {
    cambiaValoreDado(3);
    cambiaValoreDado(4);
  }
}

void resetDadi() {
  for (int i = 0; i < 7; i++) {
    dado[i] = i;
  }
}

void cambiaValoreDado(int valore) {
  for (int i = 0; i < 7; i++) {
    if (dado[i] == valore || dado[i] == 0) {
      dado[i] = -1;
    }
  }
}
