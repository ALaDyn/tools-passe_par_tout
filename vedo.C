#include <passe_par_tout.h>

int trova_simbolo(char * s)
 {const char * nomi_simboli[]={
"PUNTINO", "puntino",
"PUNTONE", "puntone",
"TONDINO_VUOTO", "tondino_vuoto",
"TONDINO_PIENO", "tondino_pieno",
"QUADRETTO_VUOTO", "quadretto_vuoto",
"QUADRETTO_PIENO", "quadretto_pieno",
"ROMBETTO_VUOTO", "rombetto_vuoto",
"ROMBETTO_PIENO", "rombetto_pieno",
"ASTERISCO", "asterisco",
"STELLINA_VUOTA", "stellina_vuota",
"STELLINA_PIENA", "stellina_piena",
"CROCETTA", "crocetta",
"CROCE_S_ANDREA", "croce_s_andrea",
"QUADRO_E_CROCE", "quadro_e_croce",
"TRIANGOLO_VUOTO", "triangolo_vuoto",
"TRIANGOLO_PIENO", "triangolo_pieno",
"NABLA_VUOTO", "nabla_vuoto",
"NABLA_PIENO", "nabla_pieno",
"PENTAGONO_VUOTO", "pentagono_vuoto",
"PENTAGONO_PIENO", "pentagono_pieno",
"PENTAGONO_DRITTO_VUOTO", "pentagono_dritto_vuoto",
"PENTAGONO_DRITTO_PIENO", "pentagono_dritto_pieno",
"ESAGONO_VUOTO", "esagono_vuoto",
"ESAGONO_PIENO", "esagono_pieno",
"ESAGONO_RUOTATO_VUOTO", "esagono_ruotato_vuoto",
"ESAGONO_RUOTATO_PIENO", "esagono_ruotato_pieno",
"OTTAGONO_VUOTO", "ottagono_vuoto",
"OTTAGONO_PIENO", "ottagono_pieno",
"STELLA_DI_DAVIDE_VUOTA", "stella_di_davide_vuota",
"STELLA_DI_DAVIDE_PIENA", "stella_di_davide_piena",
"NIDO_D_APE_VUOTO", "nido_d_ape_vuoto",
"NIDO_D_APE_PIENO", "nido_d_ape_pieno",
"\0"};
 int i = 0, r = 0;
 while(strlen(nomi_simboli[i]))
 {if(strstr(nomi_simboli[i], s)) {if(!strcmp(nomi_simboli[i], s)) return i/2; r = i/2;} i++;}
 return r < 32 ? r : 0;}

int main(int narg, char **args, char ** env)
 {int K, L, max = 0, x, y, n, M = 0, simbolo = PUNTINO, (*f[])(double[]) = {m_point, m_line};
  double X[]={1.0e+308, 1.0e+308, -1.0e+308, -1.0e+308}, *xvec, s, t;
  char * bubbola, * r, si = 0, * nome_ombra = 0;
  switch(narg)
   {default: case 4: nome_ombra = args[3];
    case 3: simbolo = trova_simbolo(args[2]);
    case 2: break;
    case 1: cout << "ci vuole almeno un nome di file\n"; return 254;}
  ifstream issa(args[1]);
  while(1) {issa . ignore(3000, '\n'); if(issa.eof()) break; max++;}
  issa . clear(), issa . seekg(0, ios :: beg),
  bubbola = new char[2001], issa . getline(bubbola, 2000), issa . seekg(0, ios :: beg),
  r = strtok(bubbola, " \t"); while(r) M++, r =  strtok((char *)NULL, " \t");
  delete [] bubbola,
  cout << "linee = " << max << " colonne = " << M << endl << flush;
  xvec = new double[M*max];
  for(K=0; K < max; K++) for(L=0; L < M; L++) issa >> xvec[M*K+L];
  issa . close(),
  cout << "che cosa vuoi graficare (due numeri interi tra 0 e " << M-1 << ") " << flush, cin >> x >> y, cin . get();
  for(K=0; K < max; K++)
   X[0] = (s = xvec[M*K+x]) < (t = X[0]) ? s : t,
   X[2] = (s = xvec[M*K+x]) > (t = X[2]) ? s : t,
   X[1] = (s = xvec[M*K+y]) < (t = X[1]) ? s : t,
   X[3] = (s = xvec[M*K+y]) > (t = X[3]) ? s : t;
  cout
   << "la scala naturale è " 
   << X[0] << ' ' <<  X[1] << ' ' <<  X[2] << ' ' << X[3]
   << " ti garba ? [S] " << flush;
  si = cin . get();
  if(si != '\n' && si != 's' && si != 'S')
   cout << "allora dimmene una che ti garbi ", cin >> X[0] >> X[1] >> X[2] >> X[3], cin . get();
  m_startg((char*)"fase", &(K=600), &(L=600));
  if(nome_ombra) m_window(&(K=OMBREGGIA_FINESTRA), &(L=OMBREGGIA_FINESTRA), nome_ombra);
  else m_window(&(K=0), &(L=0));
  K = 1, si = 0;
  if(max > 200) m_use_as_pixmap(&(K=1), &(L=BIANCO)), K = 0;
  if(K)
   cout << "sto per usare la funzione m_line; ti garba ? [S] " << flush, si = cin . get();
  if(si && si != '\n' && si != 's' && si != 'S') K = 0;
  m_frame(X, X+1, X+2, X+3), m_symbol(&simbolo),
  X[0] = xvec[x], X[1] = xvec[y], m_move(X);
  for(n=0; n < max; n++) X[0] = xvec[M*n + x], X[1] = xvec[M*n + y], (*f[K])(X);
  m_wait_for_events(&(K=EVENTO_ENTER)), m_endg();}
