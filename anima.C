# include <passe_par_tout.h>

int main(int narg, char ** args, char ** env)
 {int K = 200, L = 200;
  unsigned int
   m = ORDINE_NATURALE,
   M[]={RISALTO | MAGENTA, STELLA | ROSSO, MOVIOLA | BLU, PLAY | BIANCO, SFONDO | NERO, 0};
  char z=0;
  m_startg((char *)" ", &K, &L),
  m_toggle_message(),
  m_sound_message(&z),
  m_animate(args[1], &m, 0),
  m_endg();}

