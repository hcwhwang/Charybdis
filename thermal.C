double kN(int nE)
{
  double kn=pow((2*TMath::Pi()),nE);
  kn=kn*TMath::Gamma((3.+nE)/2.)/(nE+2.);
  kn=kn/pow(TMath::Pi(),(nE+3.)/2.);
  kn=pow(kn,1./(nE+1.));
  return kn;
}

double rS(int nE,double mBh)
{
  double mD=1.;
  rs=kN(nE)*pow(mBh/mD,1./(nE+1.))/mD;
  return rs;
}

double rH(int nE,double mBh,double aStar)
{
  double rh=rS(nE,mBh);
  rh=rh/pow(1+aStar*aStar,1./(nE+1.));
  return rh;
}
double tH(int nE,double mBh,double aStar)
{
  double th=(nE+1.)+(nE-1.)*aStar*aStar;
  th=th/(4.*TMath::Pi())/rH(nE,mBh,aStar)/(1.+aStar*aStar);
  return th;
}
double omega(int nE, double mBh, double aStar)
{
  return aStar/(1.+aStar*aStar)/rH(nE,mBh,aStar);
}
double factor(int nE,double mBh, double aStar,double w,float m,int s)
{
  return 1./(exp((w-m*omega(nE,mBh,aStar))/tH(nE,mBh,aStar))-pow(-1,s));
}
void thermal()
{
  TGraph* gN2 = new TGraph();
  gN2->SetLineWidth(3);
  gN2->SetLineColor(kRed);
  TGraph* gN6 = new TGraph();
  gN6->SetLineWidth(3);
  gN6->SetLineColor(kBlue);
  double wMin=0;
  double wMax=2;
  double wStep=0.01;
  int nWPoint=(wMax-wMin)/wStep;
  double aStar=0;
  int m=0;
  double w;
  for(int i=0;i<=nWPoint;i++)
  {
    w=wMin+wStep*i;
    gN2->SetPoint(i,w,factor(2,14,aStar,w,m,1));
    gN6->SetPoint(i,w,factor(6,14,aStar,w,m,1));
  }
  TCanvas*c = new TCanvas("c","c",500,500);
  gN2->Draw("al");
  gN6->Draw("same");
}

