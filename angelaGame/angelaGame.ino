int meta;
int dado[7] = {0, 1, 2, 3, 4, 5, 6};
int turno = -1;
int dadoGiocato;

void setup() {
  Serial.begin(9600);
}


void loop() {
  if (turno == -1) {
    while (Serial.available() == 0 && meta == 0)
    {
      meta = Serial.parseInt();
      Serial.println("META = " + String(meta));
    }
    Serial.println("META = " + String(meta));
    turno = 0;
  } else {
    if (turno % 2 == 0) {
      sceltaDado();
      if (dadoValido(dadoGiocato)) {
        cambiaDadiGiocabili(dadoGiocato);
      } else {
        Serial.println("DADO NON VALIDO");
      }
    } else {

    }
  }
}

void sceltaDado() {
  while (Serial.available() == 0) {
    dadoGiocato = Serial.parseInt();
    Serial.println("DADO = " + String(dadoGiocato));
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
  }
  if (dadoGiocato == 1 || dadoGiocato == 6) {
    cambiaValoreDado(1);
    cambiaValoreDado(6);
  }
  if (dadoGiocato == 2 || dadoGiocato == 5) {
    cambiaValoreDado(1);
    cambiaValoreDado(6);
  }
  if (dadoGiocato == 3 || dadoGiocato == 4) {
    cambiaValoreDado(1);
    cambiaValoreDado(6);
  }
}

void cambiaValoreDado(int valore) {
  for (int i = 0; i < 7; i++) {
    if (dado[i] == valore || dado[i] == 0) {
      dado[i] = -1;
    } else {
      dado[i] = i;
    }
  }
}
