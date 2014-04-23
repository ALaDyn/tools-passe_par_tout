#include <passe_par_tout.h>

int main(int narg, char **args, char ** env)
 {char * bubbola, * r;
  double X[4], *xvec;
  ifstream issa;
  int i, j, K, L, max, x, y, n, M, simbolo = PUNTINO;
  if(narg < 3) {cout << "mancano argomenti: a.out file_scala file_temp file_film *\n"; return 255;}
  issa . open(args[1]), issa >> X[0] >> X[1] >> X[2] >> X[3] >> x >> y, issa . close(),
  m_startg((char*)"fase", &(K=600), &(L=600)),
  m_window(&(K=0), &(L=FINESTRA_DOPPIA)),
  m_use_as_pixmap(&(K=-1), &(L=BIANCO)),
  m_frame(X, X+1, X+2, X+3),
  m_symbol(&simbolo),
  L = 3, j = 1;
  while(/*++L,*/++L < narg)
   {m_clear_pixmap(&(K=1), &(i=BIANCO)),
    issa . open(args[L]),
    max = M = 0;
    while(1)
      {
	issa . ignore(3000, '\n');
	if(issa.eof()) break;
	max++;
      }
    issa . clear(), issa . seekg(0, ios :: beg),
    bubbola = new char[2001], issa . getline(bubbola, 2000), issa . seekg(0, ios :: beg),
    r = strtok(bubbola, " \t"); while(r) M++, r =  strtok((char *)NULL, " \t");
    if(M < x+1 || M < y+1) {issa . clear(), issa . close(); continue;}
    xvec = new double[M*max];
    for(i=0; i < max; i++) for(n=0; n < M; n++) issa >> xvec[M*i+n];
    issa . clear(), issa . close();
      //    X[0] = xvec[x], X[1] = xvec[y], m_move(X);
    for(n=0; n < max; n++) X[0] = xvec[M*n + x], X[1] = xvec[M*n + y], m_point(X);
    delete [] xvec,
    m_show_pixmap(&(K=1)),
    m_redraw(&(K=0)),
/*
    sprintf(bubbola, "%s%.7i", args[2], j++),
    m_save_window(&K, bubbola),*/
    delete [] bubbola,
    /*cout <<*/ m_write_owned_photogram(&(K=0), args[2], &j) /*<< endl*/, j++;
    //   if(!(j % 100)) cout << j << '\r';
}
  m_endg();
  cout << "sto per montare il film " << args[2] << " in " << args[3] << endl;
  m_mount_owned_film(args[2], args[3], 0);}

