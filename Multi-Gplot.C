//  opzioni alla fine!!!!
//
//

#include<passe_par_tout.h>


#define n_colori 64
#define VOID -100000

#define MAX(x,y) ((x)>=(y)?(x):(y))     
#define MIN(x,y) ((x)<=(y)?(x):(y)) 
#define TRUE 1
#define FALSE 0

int FORMATTED;

int *scala_colori_pos, *scala_colori_neg;

void graph(int FLAG_PS, int nx, int ny)
{
  int ix, iy, fx, fy;
  
  ix=nx;//800;
  iy=ny;//660;
  fx=100;//(nx*100)/ix;
  fy=100;//(ny*100)/iy;
  m_startg("window", &ix, &iy);

  if (FLAG_PS) ix=fx|0x80000000;
  else ix=fx;
  iy=fy;

  m_window(&ix, &iy);
  //m_toggle_mouse_save_right(&(ix=0));
  m_use_as_pixmap(&(ix=1), &(iy=7));
  
  //m_toggle_message();
}

void definisciScalaColori_NEW_OLD(int FLAG_WHITE)
{
  int i, flag=1;
  double x, y,r, g, b, croma, h,c,v, RGB[3];
  
  scala_colori_pos=new int [n_colori];    
  scala_colori_neg=new int [n_colori];    
  printf("ciao FLAG_WHITE=%i\n",FLAG_WHITE);
  if(FLAG_WHITE==0)
    for (i=0; i<n_colori; i++)
      {
	x=i*1.0/n_colori;      
	y=1.0-x;
	h =(1.0+0.12*(1.6-2.4*y))-(int)((1.0+0.12*(1.6-2.4*y)));
	c =1.0;//0.6666+x;
	v =(1.0-exp(-6.0*x))/(1.0+exp(-6.0*x));//1.0-exp(-3.0*x);//(1.5+1.0*x)/2.5;
	if(i==0)
	  h =c=v=FLAG_WHITE,c=0;
	scala_colori_neg[i]=m_new_color_hcv(&h, &c, &v, &flag, RGB);
	
	h =0.66666-0.12*(1.7-2.5*y);
	c =1.0;//0.6666+x;
	v =(1.0-exp(-6.0*x))/(1.0+exp(-6.0*x));//1.0-exp(-3.0*x);//(1.5+1.0*x)/2.5;
	if(i==0)
	  h =c=v=FLAG_WHITE,c=0;
	scala_colori_pos[i]=m_new_color_hcv(&h, &c, &v, &flag, RGB);
	
      } 
  else
    {printf("ciao FLAG_WHITE=%i\n",FLAG_WHITE);
    for (i=0; i<n_colori; i++)
      {
	x=i*1.0/n_colori;      
	y=1.0-x;
	h =(1.0+0.12*(1.6-2.4*y))-(int)((1.0+0.12*(1.6-2.4*y)));
	c =1.0-exp(6*(-1+x));//1.0;//0.6666+x;
	v =(1.0-exp(-6.0*(x+0.9/n_colori)))/(1.0+exp(-6.0*x));//1.0-exp(-3.0*x);//(1.5+1.0*x)/2.5;
	if(i==0)
	  h =c=v=FLAG_WHITE,c=0;
	scala_colori_neg[i]=m_new_color_hcv(&h, &c, &v, &flag, RGB);
	
	h =0.66666-0.12*(1.7-2.5*y);
	c =1.0-exp(6*(-1+x));//0.6666+x;
	v =(1.0-exp(-6.0*(x+0.9/n_colori)))/(1.0+exp(-6.0*x));//1.0-exp(-3.0*x);//(1.5+1.0*x)/2.5;
	if(i==0)
	  h =c=v=FLAG_WHITE,c=0;
	scala_colori_pos[i]=m_new_color_hcv(&h, &c, &v, &flag, RGB);
	
      } 
    }
}   

void definisciScalaColori_unica_OLD(int FLAG_WHITE)
{
  int i, flag=1;
  double x, y, z, alpha, csi, r, g, b, croma, h, c, v, RGB[3];
  
  scala_colori_pos=new int [n_colori];    
  scala_colori_neg=new int [n_colori]; 
  
  for (i=0; i<n_colori; i++)
    {
      
      x=i*1.0/n_colori;   

      
      y=(1.0-exp(-8.0*x))/(1.0+exp(-8.0*x));
      if(x>0.5)
	z=x-0.55-9*(x-0.5)*(x-0.5);
      else
	z=x-0.5;
      if (x<0.1) croma=x/0.1; else croma=1; croma=sqrt(croma);
      
      r=y*pow(fabs(sin((x-0.2)*M_PI)),1.5)*croma;//r=y*pow(fabs(sin((x-0.3)*M_PI)),1.2)*croma;
      g=y*pow(cos(z*M_PI),1.8);//g=y*pow(sin(x*M_PI),1.8);
      b=y*pow(cos(0.55*x*M_PI),1.8)*croma;//b=y*pow(cos(0.5*x*M_PI),1.1)*croma;
      if (i==0&&FLAG_WHITE)
      r=g=b=1;
      
      scala_colori_pos[i]=scala_colori_neg[i]=m_new_color(&r, &g, &b);
      
    }    
}  

void definisciScalaColori_unica_HOT(int FLAG_WHITE, double GAMMA)
{
  int i, flag=1;
  double x, y, z, r, g, b, RGB[3];
  int N1=24, N2=48;
  scala_colori_pos=new int [n_colori];    
  scala_colori_neg=new int [n_colori]; 
  
  for (i=0; i<N1; i++)
    {
      r=(10.+i*(255.-10.)/(N1-1.))/255.;
      g=0.;
      b=0.;
           
      scala_colori_pos[i]=scala_colori_neg[i]=m_new_color(&r, &g, &b);
    }
  for (; i<N2; i++)
    {
      r=1.;
      g=(i+1.-N1)/(N2-N1);
      b=0.;
      
      scala_colori_pos[i]=scala_colori_neg[i]=m_new_color(&r, &g, &b);
    }

  for (; i<n_colori; i++)
    {
      r=1.;
      g=1.;
      b=(i+1.-N2)/(n_colori-N2);
      
      scala_colori_pos[i]=scala_colori_neg[i]=m_new_color(&r, &g, &b);
    }
      
}  


void definisciScalaColori(int FLAG_WHITE, double GAMMA)
{
  int i, flag=1;
  double x, y, z, r, g, b, RGB[3];
  int N1=24, N2=48;
  double FN1=N1*1.0/n_colori, FN2=N2*1.0/n_colori;
  scala_colori_pos=new int [n_colori];    
  scala_colori_neg=new int [n_colori]; 
  /*
  for (i=0; i<N1; i++)
    {
      r=(10.+i*(255.-10.)/(N1-1.))/255.;
      g=0.;
      b=0.;
          
      scala_colori_pos[i]=m_new_color(&b, &g, &r);
      scala_colori_neg[i]=m_new_color(&r, &g, &b);
    }
  for (; i<N2; i++)
    {
      r=1.;
      g=(i+1.-N1)/(N2-N1);
      b=0.;
      
      scala_colori_pos[i]=m_new_color(&b, &g, &r);
      scala_colori_neg[i]=m_new_color(&r, &g, &b);
    }

  for (; i<n_colori; i++)
    {
      r=1.;
      g=1.;
      b=(i+1.-N2)/(n_colori-N2);
      
      scala_colori_pos[i]=m_new_color(&b, &g, &r);
      scala_colori_neg[i]=m_new_color(&r, &g, &b);
    }
    */
  for (i=0; i<n_colori; i++)
    {
      x=(i*1.)/(n_colori-1);
      x=pow(x,GAMMA);
      if(x<FN1)
	{
	  double OFF=5.;
	  r=(OFF+x*(255.-OFF)/FN1)/255.;
	  g=0.;
	  b=0.;
	  scala_colori_neg[i]=m_new_color(&b, &g, &r);
	  OFF=5.;
	  r=(OFF+x*(255.-OFF)/FN1)/255.;
	  
	  scala_colori_pos[i]=m_new_color(&r, &g, &b);
	}
      else if(x<FN2)
	{
	  r=1.;
	  g=(x-FN1)/(FN2-FN1);
	  b=0.;
	  
	  scala_colori_neg[i]=m_new_color(&b, &g, &r);
	  scala_colori_pos[i]=m_new_color(&r, &g, &b);
	}
      else
	{
	  r=1.;
	  g=1.;
	  b=(x-FN2)/(1-FN2);
	  
	  scala_colori_neg[i]=m_new_color(&b, &g, &r);
	  scala_colori_pos[i]=m_new_color(&r, &g, &b);
	}
    }
  
}  



void definisciScalaColori_unica(int FLAG_WHITE)
{
  int i, flag=1;
  double x, y, z, alpha, csi, r, g, b, croma, h, c, v, RGB[3];
  
  scala_colori_pos=new int [n_colori];    
  scala_colori_neg=new int [n_colori]; 
  
   for (i=0; i<8; i++)
    {
      
      r=0.;
      g=0.;
      b=(59.+i*28.)/256.;
      scala_colori_pos[i]=scala_colori_neg[i]=m_new_color(&r, &g, &b);
    }
  for (; i<24; i++)
    {
      
      r=0.;
      g=(16.*(i-7))/256.;
      b=1.;
      scala_colori_pos[i]=scala_colori_neg[i]=m_new_color(&r, &g, &b);
    }
  for (; i<40; i++)
    {
      
      r=(16.*(i-23))/256.;
      g=1.;
      b=(256-16.*(i-23))/256.;
      scala_colori_pos[i]=scala_colori_neg[i]=m_new_color(&r, &g, &b);
    }
  for (; i<56; i++)
    {
      
      r=1.;
      g=(256-16.*(i-39))/256.;
      b=0.;
      scala_colori_pos[i]=scala_colori_neg[i]=m_new_color(&r, &g, &b);
    }
  for (; i<64; i++)
    {
      
      r=(256-16.*(i-55))/256.;
      g=0.;
      b=0.;
      scala_colori_pos[i]=scala_colori_neg[i]=m_new_color(&r, &g, &b);
    }      
      
}  

 
void fscanf3i(FILE *f, char *frmt, int *p1, int *p2, int *p3)
{
  int pp3i[3];

  if (FORMATTED)
    fscanf(f, frmt, p1, p2, p3);
  else
    {
      fread(pp3i, sizeof(int), 3, f); 
      *p1=pp3i[0];
      *p2=pp3i[1];
      *p3=pp3i[2];
    }
}

void fscanf1(FILE *f, char *frmt, double *p1)
{
  double pp1[1];

  if (FORMATTED)
    fscanf(f, frmt, p1);
  else
    {
      fread(pp1,sizeof(double), 1, f);
      *p1=pp1[0];
    }
}

void fscanf2(FILE *f, char *frmt, double *p1, double *p2)
{
  double pp2[2];

  if (FORMATTED)
    fscanf(f, frmt, p1, p2);
  else
    {
      fread(pp2,sizeof(double), 2, f);
      *p1=pp2[0];
      *p2=pp2[1];
    }
}

void fscanf4(FILE *f, char *frmt, double *p1, double *p2, double *p3, double *p4)
{
  double pp4[2];

  if (FORMATTED)
    fscanf(f, frmt, p1, p2, p3, p4);
  else
    {
      fread(pp4,sizeof(double), 4, f);
      *p1=pp4[0];
      *p2=pp4[1];
      *p3=pp4[2];
      *p4=pp4[3];
    }
}

void analizeFile(char *name)
{
  int lungh;
  char cmd[200];
  FILE *f;

  sprintf(cmd, "file %s | fgrep ASCII > /tmp/ciccio_pluto", name);
  system (cmd);

  f=fopen("/tmp/ciccio_pluto", "r");
  fseek(f, 0, SEEK_END);
  lungh=ftell(f);
  fclose(f);

  sprintf(cmd, "rm -rf /tmp/ciccio_pluto");
  system (cmd);

  
  if (lungh==0) 
    {
      FORMATTED=0;

      printf(".. the file is NOT formatted \n\n");
    }
  else 
    {
      FORMATTED=1;

      printf(".. the file is formatted \n\n");
    }
    
}

void w_color_map(double min, double max, int flag_ps, int flag_film, int number, int flag_log, int flag_unica, int flag_zero)
{
  int ix, iy, k, i, nnn=1, modo, j, XI, DXI;
  double XX, DX;
  double estremi[]={0,min,1,max}, X[8], dy_n, dy_p, dy, position[2];
  int qxl=0, qxh=0, qyl=7, qyr=0,alt[]={100,0,2,0};
  char *titolo="", *assex="", *assey="", zero[24], *nome_legenda="legenda_newGplot";
  int larghezza_w, altezza_w, L[]={2,-2};
  

  printf("min=%g \n", min);
  /*
    larghezza_w=180;
  altezza_w=700;
  
  if(flag_ps)ix=60|0x80000000;
  else ix=60;
  //ix=60|0x80000000;
  iy = (90<<24) + (larghezza_w << 11) + altezza_w;
  
  k=m_window(&ix, &iy);
  m_toggle_mouse_save_right(&(k=1));
  if(!flag_ps)  m_use_as_pixmap(&(ix=1), &(iy=7));
  //m_toggle_message();
  */
  //m_frame(&estremi[0],&estremi[1],&estremi[2],&estremi[3]);
  m_select_frame(&(k=0), L);
  m_thickness(&(ix=0));
  dy_n=fabs(min/n_colori);
  dy_p=max/n_colori;
  for(i=0;i<n_colori;i++)
    {
      X[0]=0, X[1]=min+i*dy_n;
      X[2]=1, X[3]=min+i*dy_n;
      X[4]=1, X[5]=min+(i+1)*dy_n;
      X[6]=0, X[7]=min+(i+1)*dy_n;
            
      m_color(&scala_colori_neg[n_colori-1-i]);
      m_polygon(X, &(k=4));
    }
  for(i=0;i<n_colori;i++)
    {
      X[0]=0, X[1]=i*dy_p;
      X[2]=1, X[3]=i*dy_p;
      X[4]=1, X[5]=(i+1)*dy_p;
      X[6]=0, X[7]=(i+1)*dy_p;
            
      m_color(&scala_colori_pos[i]);
      m_polygon(X, &(k=4));
    }
  
  m_color(&(k=0));
  if((!flag_log))//if(!flag_ps)
    {
      if(flag_zero)
	{
	  m_how_clip(&(modo=2)); //consento di vedere a schermo cose fuori dal sistema di riferimento
	  position[0]=-0.4, position[1]=0.-0.5*dy_p;
	  sprintf(zero,"0");
	  m_text(zero, position);
	  position[0]=-0.1, position[1]=0;
	  m_move(position), position[0]=0.; 
	}
    }
  else
    {
      if(flag_unica&&(min>0))//&&(fabs((max+min)/(max-min))>0.1))
	{
	  m_how_clip(&(modo=2)); //consento di vedere a schermo cose fuori dal sistema di riferimento
	  XX=log10(max)-log10(min);
	  XI=(int)XX;
	  DX=(max-dy_p)/XX;
	  printf("XX=%f  XI=%i   DX=%e  dy=%e\n",XX, XI, DX, dy);
	  for(i=0;i<=XI;i++)
	    for(j=1;j<10;j++)
	      {
		position[0]=-1.5, position[1]=dy_p*(1.2)+DX*i+DX*log10(j);
		if(position[1]>max)continue;
		
		if(j<2)
		  sprintf(zero,"%.0e",min*j*pow(10.,i)),
		    m_text(zero, position);
		position[0]=0., position[1]=dy_p+DX*i+DX*log10(j);
		m_move(position);
		if(j==1)
		  m_thickness(&(ix=2)), position[0]=0.18;
		else
		  m_thickness(&(ix=0)), position[0]=0.10;

		m_line(position);
		
	      }
	}
    }

  //  if(flag_film)
  // m_write_photogram(&(k=1), nome_legenda, &number);
  //mchiudi_ps();
  L[0]=1;
  m_select_frame(&(k=0), L);
}



int main(int narg, char **args)
{
  int i, ii,j, n, nphotog=1, ncol, icol, jx, jy, nx, ny, aiuto=1,
    FLAG_PS=0, FLAG_WHITE=0, count, FLAG_FILM=0, FLAG_MAXDENS=0, FLAG_MINDENS=0, FLAG_CLOSERAPID=0, narg_last, FLAG_UNICA=0, FLAG_LOGSCALE=0, FLAG_OLDCOLOUR=0, FLAG_HOT=0,FLAG_RATIO=0,FLAG_SMALL=0, FLAG_BIG=0, FLAG_ZERO=0 ;
  int FLAG_XLABEL=0, FLAG_YLABEL=0, FLAG_ZLABEL=0, FLAG_TITLE=0, FLAG_FILENAME=0;
  int off_title=10, off_xlabel=10, off_ylabel=10, off_zlabel=10;
  double **growth_matrix, dx, dy, s0, tune_dep, growth,  x[8], integrale, value[100];
  double xmin, ymin, xmax, ymax, gr_max_ins, gr_minpos_ins, gr_minneg_ins, gr_min_ins;
  double log_grmin, log_grmax, log_minneg, log_minpos, gr_max, gr_min, gr_minpos, gr_minneg, log_matrix;
  int FLAG_MINPOS=0, FLAG_MINNEG=0, FLAG_PROPORTION=0;
  int iVoid[3];
  double dVoid[4];
  char *stringa=new char [20], XLABEL[40],YLABEL[40],ZLABEL[40],TITLE[40];
  char beta_ref[100], filename[100], comando[200];
  FILE *f, *g;
  int colori_buffer[n_colori];
  double XMIN, XMAX, YMIN, YMAX, EXTREM[4];
  int flag_XMIN=0,flag_XMAX=0,flag_YMIN=0,flag_YMAX=0, FLAG_column=0, mycolumn, NX, NY, esco;
  double GAMMA=1.,punto[2],dummy ;
  char tacche[]={3,3,0,0}, formato[]={'f','f','f','g'}, cifre[]={0,0,0,1};

  //int qxl=0, qxh=0, qyl=5, qyr=0,alt[]={100,0,2,0};
  //char *titolo="titolo", *assex="assex", *assey="asse y"; 
  if (narg<2)
    {
      printf("usage: file1 file2 ....  [#col (only if ncol>1)] [-psb/-psw] [-film] [-minv XX] [-maxv XX] [-minneg XX] [-minpos XX] [-unica] [-log] [-close] [-old] [-hot] [-w]\n");
      exit(-1);
    }
  printf("Benvenuto\n");
  fflush(stdout);
  for(i=1;i<narg;i++)
    {
      if (args[narg-i][0]=='^')
	{
	  flag_XMIN=FALSE;
	  flag_XMAX=TRUE;
	  sscanf(args[narg-i], "^%lf", &EXTREM[2]);
	}
      else 
	if (args[narg-i][strlen(args[narg-i])-1]=='^')
	  {
	    flag_XMIN=TRUE;
	    flag_XMAX=FALSE;
	    sscanf(args[narg-i], "%lf^", &EXTREM[0]);
	  }
	else 
	  if (strstr(args[narg-i], "^"))
	    {
	      flag_XMIN=TRUE;
	      flag_XMAX=TRUE;
	      sscanf(args[narg-i], "%lf^%lf", &EXTREM[0], &EXTREM[2]);
	    }
	  
      
      //ora estremi per la y
      if (args[narg-i][0]=='#')
	{
	  flag_YMIN=FALSE;
	  flag_YMAX=TRUE;
	  sscanf(args[narg-i], "#%lf", &EXTREM[3]);
	}
      else if (args[narg-i][strlen(args[narg-i])-1]=='#')
	{
	  flag_YMIN=TRUE;
	  flag_YMAX=FALSE;
	  sscanf(args[narg-i], "%lf#", &EXTREM[1]);
	}
      else 
	if (strstr(args[narg-i], "#"))
	  {
	    flag_YMIN=TRUE;
	    flag_YMAX=TRUE;
	    sscanf(args[narg-i], "%lf#%lf", &EXTREM[1], &EXTREM[3]);
	    
	  }
    }

  /**************************************************************/
  


  for (i=1; i<narg; i++)
    if (args[i][0]=='-') break;
  narg_last=i;

  for (i=1; i<narg; i++)
    if (!strncmp(args[i], "-psb",4)) FLAG_PS=1;
 
  for (i=1; i<narg; i++)
    if (!strncmp(args[i], "-psw",4)) FLAG_PS=1, FLAG_WHITE=1;

  for (i=1; i<narg; i++)
    if (!strncmp(args[i], "-w",2)) FLAG_WHITE=1;

  for (i=1; i<narg; i++)
    if (!strncmp(args[i], "-film",5)) FLAG_FILM=1;

  for (i=1; i<narg; i++)
    if (!strncmp(args[i], "-close",6)) FLAG_CLOSERAPID=1;

  for (i=1; i<narg; i++)
    if (!strncmp(args[i], "-unica",6)) FLAG_UNICA=1;
  for (i=1; i<narg; i++)
    if (!strncmp(args[i], "-log",4)) FLAG_LOGSCALE=1;
  for (i=1; i<narg; i++)
    if (!strncmp(args[i], "-old",4)) FLAG_OLDCOLOUR=1;
  for (i=1; i<narg; i++)
    if (!strncmp(args[i], "-hot",4)) FLAG_HOT=1;
  for (i=1; i<narg; i++)
    if (!strncmp(args[i], "-ratio",6)) FLAG_RATIO=1;
  for (i=1; i<narg; i++)
    if (!strncmp(args[i], "-prop",5)) FLAG_PROPORTION=1;
  for (i=1; i<narg; i++)
    if (!strncmp(args[i], "-big",4)) FLAG_BIG=1;
  for (i=1; i<narg; i++)
    if (!strncmp(args[i], "-small",6)) FLAG_SMALL=1;
  for (i=1; i<narg; i++)
    if (!strncmp(args[i], "-zero",5)) FLAG_ZERO=1;
  

  for (i=1; i<narg; i++)
    if (!strncmp(args[i], "-maxv",5)) 
      {
	FLAG_MAXDENS=1;
	gr_max_ins=atof(args[i+1]);
      }
  for (i=1; i<narg; i++)
    if (!strncmp(args[i], "-minpos",7)) 
      {
	FLAG_MINPOS=1;
	gr_minpos_ins=atof(args[i+1]);
      }
  for (i=1; i<narg; i++)
    if (!strncmp(args[i], "-minneg",7)) 
      {
	FLAG_MINNEG=1;
	gr_minneg_ins=atof(args[i+1]);
      }
  for (i=1; i<narg; i++)
    if (!strncmp(args[i], "-minv",5))
      {
        FLAG_MINDENS=1;
        gr_min_ins=atof(args[i+1]);
      }
  for (i=1; i<narg; i++)
    if (!strncmp(args[i], "-col",4))
      {
	FLAG_column=1;
        mycolumn=atoi(args[i+1]);
      }
  for (i=1; i<narg; i++)
    if (!strncmp(args[i], "-gamma",6))
      {
	GAMMA=atof(args[i+1]);
      }
   for (i=1; i<narg; i++)
    if (!strncmp(args[i], "-tacx",5))
      {
	tacche[0]=(int)atoi(args[i+1]);
      }
   for (i=1; i<narg; i++)
    if (!strncmp(args[i], "-tacy",5))
      {
	tacche[1]=(int)atoi(args[i+1]);
      }
   for (i=1; i<narg; i++)
    if (!strncmp(args[i], "-tacz",5))
      {
	tacche[3]=(int)atoi(args[i+1]);
      }
   for (i=1; i<narg; i++)
    if (!strncmp(args[i], "-digx",5))
      {
	cifre[0]=(int)atoi(args[i+1]);
      }
   for (i=1; i<narg; i++)
    if (!strncmp(args[i], "-digy",5))
      {
	cifre[1]=(int)atoi(args[i+1]);
      }
   for (i=1; i<narg; i++)
    if (!strncmp(args[i], "-digz",5))
      {
	cifre[3]=(int)atoi(args[i+1]);
      }
   for (i=1; i<narg; i++)
    if (!strncmp(args[i], "-xlabel",7))
      {
	FLAG_XLABEL=1;
	sprintf(XLABEL,"%s",args[i+1]);
      }
   for (i=1; i<narg; i++)
    if (!strncmp(args[i], "-ylabel",7))
      {
	FLAG_YLABEL=1;
	sprintf(YLABEL,"%s",args[i+1]);
      }
    for (i=1; i<narg; i++)
    if (!strncmp(args[i], "-zlabel",7))
      {
	FLAG_ZLABEL=1;
	sprintf(ZLABEL,"%s",args[i+1]);
      }
    sprintf(TITLE,"");
   for (i=1; i<narg; i++)
    if (!strncmp(args[i], "-title",6))
      {
	FLAG_TITLE=1;
	sprintf(TITLE,"%s %s",TITLE,args[i+1]);
      }
   for (i=1; i<narg; i++)
    if (!strncmp(args[i], "-offxlabel",10))
      {
	off_xlabel=(int)atoi(args[i+1]);
      }
   for (i=1; i<narg; i++)
    if (!strncmp(args[i], "-offylabel",10))
      {
	off_ylabel=(int)atoi(args[i+1]);
      }
   for (i=1; i<narg; i++)
    if (!strncmp(args[i], "-offzlabel",10))
      {
	off_zlabel=(int)atoi(args[i+1]);
      }
   for (i=1; i<narg; i++)
    if (!strncmp(args[i], "-offtitle",9))
      {
	off_title=(int)atoi(args[i+1]);
      }
   for (i=1; i<narg; i++)
    if (!strncmp(args[i], "-o",2))
      {
	FLAG_FILENAME=1;
	sprintf(filename,"%s",args[i+1]);
      }
   
 printf("Benvenuto\n");
  fflush(stdout);
  
 
  for (i=1; i<narg; i++)
    {
      if (f=fopen(args[i], "r"))
	{
	  analizeFile(args[i]);
	  fscanf3i(f, "%i %i %i", &nx, &ny, &ncol);
	  fscanf4(f, "%lf %lf %lf %lf", &xmin, &ymin, &xmax, &ymax);
	  fclose(f);
	  break;
	}
    }
  
  printf("nx/ny = %i/%i   ncol = %i\n", nx, ny, ncol);
  printf("xmin,ymin,xmax,ymax= %f %f %f %f \n", xmin, ymin, xmax, ymax);

  dx=(xmax-xmin)/(nx-1), dy=(ymax-ymin)/(ny-1);

  XMIN=xmin, YMIN=ymin;
  XMAX=xmax, YMAX=ymax;
  NX=nx,     NY=ny;
  if(flag_XMIN)//&&(XMIN<EXTREM[0]))
    xmin=EXTREM[0];
  else
    xmin=XMIN;
  if(flag_YMIN)//&&(YMIN<EXTREM[1]))
    ymin=EXTREM[1];
  else
    ymin=YMIN;
  
  if(flag_XMAX)//&&(XMAX>EXTREM[2]))
    xmax=EXTREM[2];
  else
    xmax=XMAX;
  if(flag_YMAX)//&&(YMAX>EXTREM[3]))
    ymax=EXTREM[3];
  else
    ymax=YMAX;
  
  nx=(int)((xmax-xmin)/dx+1), ny=(int)((ymax-ymin)/dy+1);
  dummy=MIN(dx,dy);
  NX=(int)((xmax-xmin)/dummy+1), NY=(int)((ymax-ymin)/dummy+1);
  if(NY>550)
    {
      dummy=1.*550/NY;
      NY=(int)(dummy*NY);
      NX=(int)(dummy*NX);
    }
  if(NX>550)
    {
      dummy=1.*550/NX;
      NY=(int)(dummy*NY);
      NX=(int)(dummy*NX);
    }
  if(FLAG_BIG)
    graph(FLAG_PS, 1100, 900);
  else if(FLAG_SMALL)
    graph(FLAG_PS, 640, 480);
  else
    graph(FLAG_PS, 800, 660);
  if(FLAG_UNICA)
    {
      if(FLAG_OLDCOLOUR)
	definisciScalaColori_unica_OLD(FLAG_WHITE);
      else if(FLAG_HOT)
	definisciScalaColori_unica_HOT(FLAG_WHITE, GAMMA);
      else
	definisciScalaColori_unica(FLAG_WHITE);
      aiuto=2;
    }
  else
    definisciScalaColori(FLAG_WHITE, GAMMA);
  if(FLAG_WHITE)
    {
      if(!FLAG_UNICA)
	/*if(!FLAG_HOT)
	  {
	    colori_buffer[0]=scala_colori_neg[0];
	    for(i=1;i<n_colori;i++)
	      colori_buffer[i]=scala_colori_neg[n_colori-i];
	    for(i=0;i<n_colori;i++)
	      scala_colori_neg[i]=colori_buffer[i];
	    colori_buffer[0]=scala_colori_pos[0];
	    for(i=1;i<n_colori;i++)
	      colori_buffer[i]=scala_colori_pos[n_colori-i];
	    for(i=0;i<n_colori;i++)
	      scala_colori_pos[i]=colori_buffer[i];
	  }
	  else*/
	  {
	    for(i=0;i<n_colori;i++)
	      colori_buffer[i]=scala_colori_neg[n_colori-i-1];
	    for(i=0;i<n_colori;i++)
	      scala_colori_neg[i]=colori_buffer[i];
	    for(i=0;i<n_colori;i++)
	      colori_buffer[i]=scala_colori_pos[n_colori-i-1];
	    for(i=0;i<n_colori;i++)
	      scala_colori_pos[i]=colori_buffer[i];
	  }
      if(FLAG_UNICA)
	{
	  for(i=0;i<n_colori;i++)
	    colori_buffer[i]=scala_colori_neg[n_colori-1-i];
	  for(i=0;i<n_colori;i++)
	    scala_colori_neg[i]=colori_buffer[i];
	  for(i=0;i<n_colori;i++)
	    colori_buffer[i]=scala_colori_pos[n_colori-1-i];
	  for(i=0;i<n_colori;i++)
	    scala_colori_pos[i]=colori_buffer[i];
	}
      
    }
  

  
  
  if ((ncol>1)&&FLAG_column)
    icol=mycolumn;
  else
    icol=0;
  printf("Hai scelto nx/ny = %i/%i   colonna = %i\n", nx, ny, icol);

  // allocazione
   
growth_matrix=new double* [nx];
    
  for (jx=0; jx<nx; jx++) 
    {
      growth_matrix[jx]=new double [ny];
      for (jy=0; jy<ny; jy++) growth_matrix[jx][jy]=VOID;  
    }
 
  
  //scala colori
  if (FLAG_MAXDENS==0 || FLAG_MINDENS==0)
    {
      gr_min=1e+300, gr_max=-1e+300;
      for (i=1; i<narg; i++) 
	{  
	  if(!strcmp(filename, args[i])) continue;
	     //if (!(f=fopen(args[narg-i], "r"))) continue;
	  if (!(f=fopen(args[i], "r"))) continue;
	  //f=fopen(args[i], "r");

	  printf("[%s] \n", args[narg-i]);
	  
	  fscanf3i(f, "%i %i %i", &iVoid[0], &iVoid[1], &iVoid[2]);
	  fscanf4(f, "%lf %lf %lf %lf", &dVoid[0], &dVoid[1], &dVoid[2], &dVoid[3]);
	  
	  while(1)
	    {
	      fscanf2(f, "%lf %lf", &s0, &tune_dep);
	      
	      for (ii=0; ii<ncol; ii++)
		fscanf1(f, "%lf", &value[ii]);
	      
	      if (feof(f)) break;
	      
	      gr_min=MIN(gr_min, value[icol]);
	      gr_max=MAX(gr_max, value[icol]);
	      log_grmin=log10(fabs(gr_min)+1.);
	      log_grmax=log10(gr_max+1.);
	    }
	  
	  fclose(f);      
	  break;
	}
    }


  if (FLAG_MAXDENS==1)
    {
      gr_max=gr_max_ins;
      log_grmax=log10(gr_max+1.);
    }
  if (FLAG_MINDENS==1)
    {
      gr_min=gr_min_ins;    
      log_grmin=log10(fabs(gr_min)+1.);
      
    }
  
  printf("valore min: %.10e   log(-min)=%f\n", gr_min,log_grmin);
  printf("valore max: %.10e   log(+max)=%f\n", gr_max,log_grmax);
  if(FLAG_LOGSCALE)
    printf("disegno in SCALA LOGARITMICA\n");
  
  if(FLAG_MINPOS)
    {
      if(gr_minpos_ins>=gr_max)
	{
	  printf("minpos é maggiore del massimo! Controlla!\n ");
	  printf("hai definito minpos=%.10e", gr_minpos_ins);
	  exit(0);
	}
      gr_minpos=gr_minpos_ins;
      log_minpos=log10(fabs(gr_minpos)+1.);
      printf("hai definito minpos=%.10e   log(+minpos)=%f\n", gr_minpos,log_minpos);
    }
  else
    {
      gr_minpos=0;
      log_minpos=log10(fabs(gr_minpos)+1.);
    }
  if(FLAG_MINNEG)
    {
      if(gr_minneg_ins<=gr_min)
	{
	  printf("minneg é minore del minimo! Controlla!\n ");
	  printf("hai definito minneg=%.10e", gr_minneg_ins);
	  exit(0);
	}
      gr_minneg=gr_minneg_ins;
      log_minneg=log10(fabs(gr_minneg)+1.);
      printf("hai definito minneg=%.10e   log(-minneg)=%f\n", gr_minneg,log_minneg);
    }
  else
    {
      gr_minneg=0;
      log_minneg=log10(fabs(gr_minneg)+1.);
    }
  {
    
    double frame[]={xmin,ymin,xmax,ymax,0,0,0,gr_min,1,gr_max,0,0}, position[2], angolo;
    int K=-2, L=2, TT,IO[]={90,70,500,500,730,70,50,500}, modo;
    
    if(FLAG_PROPORTION)
      IO[2]=NX, IO[3]=NY;
    if(FLAG_BIG)
      IO[0]=100, IO[1]=IO[5]=90, IO[2]=700, IO[3]=700, IO[4]=1000, IO[7]=700;
    else if(FLAG_SMALL)
      IO[0]=80, IO[1]=IO[5]=70, IO[2]=340, IO[3]=340, IO[4]=550, IO[6]=40, IO[7]=340;
    if(FLAG_LOGSCALE)
      tacche[3]=0;
    m_multiframe(&K, &(L=2), IO, frame);
    m_font(&(K=0), &(L=0), &(TT=7),"*", "helvetica", "medium", "r", "*", "*", "24");
    m_quote(&(K=0),tacche,formato,cifre);
    //m_frame(&xmin,&ymin,&xmax,&ymax);
    if(FLAG_UNICA)
      w_color_map(gr_minpos, gr_max,FLAG_PS ,FLAG_FILM, 1,FLAG_LOGSCALE,FLAG_UNICA,FLAG_ZERO);
    else
      w_color_map(gr_min, gr_max,FLAG_PS ,FLAG_FILM, 1,FLAG_LOGSCALE,FLAG_UNICA,FLAG_ZERO);
    m_how_clip(&(modo=2)); //consento di vedere a schermo cose fuori dal sistema di riferimento
    
    if(FLAG_XLABEL)
      {
	if(FLAG_SMALL)
	  position[0]=(xmin+xmax)*0.5-(xmax-xmin)*0.005*off_xlabel, position[1]=ymin-(ymax-ymin)*0.15;
	else
	  position[0]=(xmin+xmax)*0.5-(xmax-xmin)*0.0035*off_xlabel, position[1]=ymin-(ymax-ymin)*0.12;
	m_text(XLABEL, position);
      }
    if(FLAG_YLABEL)
      {if(FLAG_SMALL)
	  position[0]=xmin-(xmax-xmin)*0.02*off_ylabel, position[1]=(ymax+ymin)*0.5;
	else
	  position[0]=xmin-(xmax-xmin)*0.014*off_ylabel, position[1]=(ymax+ymin)*0.5;
	m_text(YLABEL, position);
      }
    if(FLAG_ZLABEL)
      position[0]=xmax+(xmax-xmin)*0.005*off_zlabel, position[1]=(ymax+ymin)*0.5,
        m_text(ZLABEL, position);
    if(FLAG_TITLE)
      position[0]=(xmin+xmax)*0.5-(xmax-xmin)*0.02*off_title, position[1]=ymax+(ymax-ymin)*0.05,
	m_text(TITLE, position);
    
  }
  

  while(1)
    {
      for(ii=1; ii<narg; ii++)
	{
	  
	  for (jx=0; jx<nx; jx++) 
	    for (jy=0; jy<ny; jy++) growth_matrix[jx][jy]=VOID; 
	  
	  if(!strcmp(filename, args[ii])) continue;
	  if (!(f=fopen(args[ii], "r"))) continue;
	  //f=fopen(args[ii], "r");

	  printf("--- %i [%s] \n", ii, args[ii]);
	  
	  fscanf3i(f, "%i %i %i", &iVoid[0], &iVoid[1], &iVoid[2]);
	  fscanf4(f, "%lf %lf %lf %lf", &dVoid[0], &dVoid[1], &dVoid[2], &dVoid[3]);
	  
	  while(1)
	    {
	      fscanf2(f, "%lf %lf", &s0, &tune_dep);
	      
	      for (i=0; i<ncol; i++)
		fscanf1(f, "%lf", &value[i]);
	      growth=value[icol];
	      
	      if (feof(f)) break;
	      
	      //if(so>=xmin&&tune_dep>=ymin)
	      //{
		  jx=(int)MIN((s0      -xmin)/dx, nx-1),
		    jy=(int)MIN((tune_dep-ymin)/dy, ny-1);
		  
		  if (jx<0||jx>=nx||jy<0||jy>=ny) continue;
		  growth_matrix[jx][jy]=growth; 
		  //	}
	    }
	  
	  fclose(f);
	  
	  for (jx=0; jx<(nx-1); jx++)
	    for (jy=0; jy<(ny-1); jy++)
	      {
		x[0]=jx*dx+xmin-0.5*dx     , x[1]=jy*dy+ymin-0.5*dy;
		x[2]=(jx+1)*dx+xmin+0.5*dx , x[3]=jy*dy+ymin-0.5*dy;
		x[4]=(jx+1)*dx+xmin+0.5*dx , x[5]=(jy+1)*dy+ymin+0.5*dy;
		x[6]=jx*dx+xmin-0.5*dx     , x[7]=(jy+1)*dy+ymin+0.5*dy;
		
		if (growth_matrix[jx][jy]!=VOID) 
		  {
		    
		    if(growth_matrix[jx][jy]<0)
		      {
			if(FLAG_LOGSCALE)
			  {
			    log_matrix=log10(fabs(growth_matrix[jx][jy])+1.);
			    i=(int)(((log_matrix-log_minneg)/(log_grmin-log_minneg))*n_colori);
			  }
			else
			  i=(int)(((growth_matrix[jx][jy]-gr_minneg)/(gr_min-gr_minneg))*n_colori);
			
			if(i>=n_colori)
			  i=n_colori-1;
			else if(i<0)
			  i=0;
			m_color(&scala_colori_neg[i]);
		      }
		    else if(growth_matrix[jx][jy]>=0)
		      {
			if(FLAG_LOGSCALE)
			  {
			    log_matrix=log10(fabs(growth_matrix[jx][jy])+1.);
			    i=(int)(((log_matrix-log_minpos)/(log_grmax-log_minpos))*n_colori);
			  }
			else
			  i=(int)(((growth_matrix[jx][jy]-gr_minpos)/(gr_max-gr_minpos))*n_colori);
			
			if(i>=n_colori)
			  i=n_colori-1;
			else if(i<0)
			  i=0;
			m_color(&scala_colori_pos[i]);
		      }
		    
		    m_polygon(x, &(i=4));
		    
		  }
		else
		  {
		    i=0;
		    m_color(&scala_colori_pos[i]);
		    m_polygon(x, &(i=4));
		  }
	      }
	  
	  m_redraw(&(jx=0));
	  if (FLAG_PS) 
	    {
	  
	      // if(FLAG_FILENAME)
	      //	sprintf(comando,"mv implicito_PS_1 %s",filename),
	      //  system(comando);
	      goto lab;
	    }

	  if (FLAG_FILM)
	    {
	      printf("... write photogram..init: %i \n", nphotog); fflush(stdout);
	      fflush(stdout);
	      m_write_photogram(&(j=0), "pp", &nphotog);
	      nphotog+=1;
	    }


	  m_wait_for_microseconds(&(jx=10000));
	  //if (m_mouse(x)==2) break;
	  //m_clear_pixmap(&(jx=1), &(jy=7));
	 
	}
      
      printf("\nfatto\n");
      fflush(stdout);
      count++;
      if (FLAG_CLOSERAPID==1 || m_mouse(x)==2) break;
      else
	while(1)
	  {
	    esco=m_mouse(punto);
	    if (esco==2)
	      {
		m_endg();
		return 0;
	      }
	    else if (esco==1)break;
	    printf("Posizione:   %.7g %.7g \n",punto[0], punto[1]);
	  }

    }

lab:
  m_endg();
  if (FLAG_PS) 
    if(FLAG_FILENAME)
      sprintf(comando,"mv implicito_PS_1 %s",filename),
	  system(comando);
}
