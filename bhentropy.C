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

double sH(int nE,double mBh,double aStar)
{
  double sh=mBh/(nE+2.)/tH(nE,mBh,aStar);
  sh=sh*(nE+1.-2.*aStar*aStar/(1.+aStar*aStar));
  return sh;
}
void bhentropy()
{
  const int nE=6;
  double mBh;
  const double mBhConst = 14.;
  double mBhMin=5.;
  double mBhMax=14.;
  double mBhStep=0.5;
  int nMBhPoint=(mBhMax-mBhMin)/mBhStep;

  double aStar;
  double aStarMin = 0.;
  double aStarMax = 5.;
  double aStarStep = 0.5;
  int nAStarPoint = (aStarMax-aStarMin)/aStarStep;
  TGraph2D* g1= new TGraph2D();
  g1->SetTitle("Black Hole Entropy;Mass;a*;Entropy");
  TGraph2D* g2= new TGraph2D();
  g2->SetTitle("Hawking Temperature;Mass;a*;T");
  TGraph* g3= new TGraph();
  g3->SetTitle("Schwarzschild Radius;Mass;r_{s}");
  TGraph* g4= new TGraph();
  g4->SetTitle("Hawking Temperature;Mass;T");
  TGraph2D* g5= new TGraph2D();
  g5->SetTitle("Black Hole Entropy;n;a*;Entropy");

  TGraph* g6= new TGraph();
  g6->SetTitle("Entropy(a*=0);n;Entropy");
  g6->SetLineColor(kRed);
  g6->SetLineWidth(2);
  g6->SetMinimum(0);
  TGraph* g7= new TGraph();
  g7->SetTitle("Entropy(a*=1);n;Entropy");
  g7->SetLineColor(kBlue);
  g7->SetLineWidth(2);
  g7->SetMinimum(0);
  TGraph* g8= new TGraph();
  g8->SetTitle("Entropy(a*=2);n;Entropy");
  g8->SetLineColor(kGreen);
  g8->SetLineWidth(2);
  g8->SetMinimum(0);
  TGraph* g9= new TGraph();
  g9->SetTitle("Entropy(a*=3);n;Entropy");
  g9->SetLineColor(kOrange);
  g9->SetLineWidth(2);
  g9->SetMinimum(0);
  TGraph* g10= new TGraph();
  g10->SetTitle("Entropy(a*=4);n;Entropy");
  g10->SetLineColor(kMagenta);
  g10->SetLineWidth(2);
  g10->SetMinimum(0);
  TGraph* g11= new TGraph();
  g11->SetTitle("Entropy(a*=5);n;Entropy");
  g11->SetLineColor(kBlack);
  g11->SetLineWidth(2);
  g11->SetMinimum(0);

  for(int n=1;n<=6;++n)
  {
    g6->SetPoint(n-1,n,sH(n,14.,0.));
    g7->SetPoint(n-1,n,sH(n,14.,1.));
    g8->SetPoint(n-1,n,sH(n,14.,2.));
    g9->SetPoint(n-1,n,sH(n,14.,3.));
    g10->SetPoint(n-1,n,sH(n,14.,4.));
    g11->SetPoint(n-1,n,sH(n,14.,5.));
  }

  TLegend* l = new TLegend(0.6,0.6,0.9,0.9);
  l->SetFillStyle(0);
  l->SetBorderSize(0);
  l->AddEntry(g6,"a*=0","l");
  l->AddEntry(g7,"a*=1","l");
  l->AddEntry(g8,"a*=2","l");
  l->AddEntry(g9,"a*=3","l");
  l->AddEntry(g10,"a*=4","l");
  l->AddEntry(g11,"a*=5","l");
  
  
  for(int i=0;i<=nMBhPoint;++i)
  { 
    mBh=mBhMin+mBhStep*i;
    for(int j=0;j<=nAStarPoint;++j)
    {
      aStar=aStarMin+aStarStep*j;
      for(int n=1;n<=6;++n)
      { 
        if(n==nE)
        {
          if (j==0) 
          {
            g3->SetPoint(i,mBh,rS(nE,mBh)); 
            g4->SetPoint(i,mBh,tH(nE,mBh,0)); 
          }
        }
      }
    }
  }
  TCanvas* c1=new TCanvas("c1","c1",500,500);
  g1->Draw("surf1");
  TCanvas* c2=new TCanvas("c2","c2",500,500);
  g2->Draw("surf1");
  TCanvas* c3=new TCanvas("c3","c3",500,500);
  g3->Draw("AL");
  TCanvas* c4=new TCanvas("c4","c4",500,500);
  g4->Draw("AL");
  TCanvas* c5=new TCanvas("c5","c5",500,500);
  g5->Draw("surf1");
  TCanvas* c6=new TCanvas("c6","c6",500,500);
  g6->Draw("al");
  g7->Draw("same");
  g8->Draw("same");
  g9->Draw("same");
  g10->Draw("same");
  g11->Draw("same");
  l->Draw();
}
