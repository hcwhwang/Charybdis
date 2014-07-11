void data()
{
  int n=2;
  ifstream flux(Form("data_files/flux_n%i.dat",n));
  TGraph* g1 = new TGraph();
  TGraph* g2 = new TGraph();
  TGraph* g3 = new TGraph();
  
  double f1,f2,f3;
  double cfluxke,cfluxkeMax,dummy;
  int i=0;
  int a0 = 7;
  int a1 = 15;
  int a2 = 15;
  int ME = 4;
  while(!flux.eof() && i != 26)
  {
    flux >> f1 >> f2 >> f3;
    g1->SetPoint(i,i*5./25.,f1);
    g1->SetTitle(Form("Scalar D=%i;a*;Number Flux",n+4));
    g2->SetPoint(i,i*5./25.,f2);
    g2->SetTitle(Form("Spinor D=%i;a*;Number Flux",n+4));
    g3->SetPoint(i,i*5./25.,f3);
    g3->SetTitle(Form("Vector D=%i;a*;Number Flux",n+4));
    ++i;
  }
  flux.close();

  ifstream fluxke(Form("data_files/cfluxke_n%i.dat",n));
  TGraph* CFLUX2S0K = new TGraph();
  CFLUX2S0K->SetTitle(Form("Scalar D=%i,a* = %f;K mode;Flux",n+4,1./5.*a0)); 
  TGraph* CFLUX2S1K = new TGraph(); 
  CFLUX2S1K->SetTitle(Form("Spinor D=%i,a* = %f;K mode;Flux",n+4,1./5.*a1)); 
  TGraph* CFLUX2S2K = new TGraph(); 
  CFLUX2S2K->SetTitle(Form("Vector D=%i,a* = %f;K mode;Flux",n+4,1./5.*a2)); 
  for(int ma=0; ma <= 25; ++ma)
  { 
    for(int k=0; k <=169;++k)
    {
      fluxke >> dummy;
      if(ma==a1 && k != 169) 
      {
        cfluxke = dummy;
        CFLUX2S0K->SetPoint(k,k+1,cfluxke);
      }
    }
  }
  for(int ma=0; ma <= 25; ++ma)
  { 
    for(int k=0; k <=156;++k)
    {
      fluxke >> dummy;
      if(ma==a1 && k != 156) 
      {
        cfluxke = dummy;
        CFLUX2S1K->SetPoint(k,k+1,cfluxke);
      }
    }
  }
  for(int ma=0; ma <= 25; ++ma)
  { 
    for(int k=0; k <=120;++k)
    {
      fluxke >> dummy;
      if(ma==a1 && k != 120) 
      {
        cfluxke = dummy;
        CFLUX2S2K->SetPoint(k,k+1,cfluxke);
      }
    }
  }
  int k0 =1;
  int j0 = pow(k0+1-1/100.,0.5);
  int m0 = k0-j0*(j0+1);

  int k1 =0;
  int j1Int = pow(k1+1-1/100.,0.5)-0.5;
  float j1 = j1Int+0.5;
  float m1 = k1+0.25-j1*(j1+1);

  int k2 =2;
  int j2 = pow(k2+1+1/100.,0.5);
  int m2 = k2+1-j2*(j2+1);

  TGraph *CFLUX2S0KE = new TGraph();
  CFLUX2S0KE->SetTitle(Form("Scalar D=%i,a*=%f,j=%i,m=%i;#omega r_{h};Cumulative Flux",n+4,1./5.*a0,j0,m0)); 
  TGraph *CFLUX2S1KE = new TGraph();
  CFLUX2S1KE->SetTitle(Form("Spinor D=%i,a*=%f,j=%i,m=%i;#omega r_{h};Cumulative Flux",n+4,1./5.*a1,j1,m1)); 
  TGraph *CFLUX2S2KE = new TGraph();
  CFLUX2S2KE->SetTitle(Form("Vector D=%i,a*=%f,j=%i,m=%i;#omega r_{h};Cumulative Flux",n+4,1./5.*a2,j2,m2)); 
  
  for(int ma=0; ma <= 25; ++ma)
  {
    for(int k=0; k <= 168; ++k)
    {
      for(int e=0; e <= 100; ++e)
      {
        fluxke >> dummy;
        if(k==k0 && ma==a0 && e!=100)
        {
          cfluxke = dummy;
          CFLUX2S0KE->SetPoint(e,(e+1)/20.,cfluxke);
        }
      }
    }
  }
  for(int ma=0; ma <= 25; ++ma)
  {
    for(int k=0; k <= 155; ++k)
    {
      for(int e=0; e <= 100; ++e)
      {
        fluxke >> dummy;
        if(k==k1 && ma==a1 && e!=100)
        {
           cfluxke = dummy;
           CFLUX2S1KE->SetPoint(e,(e+1)/20.,cfluxke);
        }
      }
    }
  }

  for(int ma=0; ma <= 25; ++ma)
  {
    for(int k=0; k <= 119; ++k)
    {
      for(int e=0; e <= 100; ++e)
      {
        fluxke >> dummy;
        if(k==k2 && ma==a2 && e!=100)
        {
          cfluxke = dummy;
          CFLUX2S2KE->SetPoint(e,(e+1)/20.,cfluxke);
        }
      }
    }
  }
  fluxke.close();
  
  g1->SetLineColor(kRed);
  g2->SetLineColor(kBlue);
  g3->SetLineColor(kGreen);
  g1->SetLineWidth(3);
  g2->SetLineWidth(3);
  g3->SetLineWidth(3);
  
  TCanvas *c = new TCanvas("c","c",500,500);
  //c->SetLogy();
  g3->Draw("al");
  g2->Draw("same");
  g1->Draw("same");
  TLegend *l = new TLegend(0.6, 0.6, 0.9, 0.9);
  l->SetFillStyle(0);
  l->SetBorderSize(0);
  l->AddEntry(g1,Form("Scalar D=%i",n+4),"l"); 
  l->AddEntry(g2,Form("Spinor D=%i",n+4),"l"); 
  l->AddEntry(g3,Form("Vector D=%i",n+4),"l"); 
  l->Draw();
  TCanvas *c2 = new TCanvas("c2","c2",500,500);
  CFLUX2S0K->SetLineColor(kRed);
  CFLUX2S1K->SetLineColor(kBlue);
  CFLUX2S2K->SetLineColor(kGreen);
  CFLUX2S0KE->SetLineColor(kRed);
  CFLUX2S1KE->SetLineColor(kBlue);
  CFLUX2S2KE->SetLineColor(kGreen);

  CFLUX2S0K->SetLineWidth(3);
  CFLUX2S1K->SetLineWidth(3);
  CFLUX2S2K->SetLineWidth(3);
  CFLUX2S0KE->SetLineWidth(3);
  CFLUX2S1KE->SetLineWidth(3);
  CFLUX2S2KE->SetLineWidth(3);
  CFLUX2S0KE->Draw("AL"); 
  TCanvas *c3 = new TCanvas("c3","c3",500,500);
  CFLUX2S1K->Draw("AL"); 
  TCanvas *c4 = new TCanvas("c4","c4",500,500);
  CFLUX2S2K->Draw("AL"); 
  TCanvas *c5 = new TCanvas("c5","c5",500,500);
  CFLUX2S0KE->Draw("AL");
  TCanvas *c6 = new TCanvas("c6","c6",500,500);
  CFLUX2S1KE->Draw("AL");
  TCanvas *c7 = new TCanvas("c7","c7",500,500);
  CFLUX2S2KE->Draw("AL");
  
}
