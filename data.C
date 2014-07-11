void data()
{
  ifstream flux("data_files/flux_n2.dat");
  TGraph* g1 = new TGraph();
  TGraph* g2 = new TGraph();
  TGraph* g3 = new TGraph();
  
  double f1,f2,f3;
  double cfluxke,cfluxkeMax,dummy;
  int i=0;
  int a1 = 7;
  int a2 = 15;
  int a3 = 15;
  int ME = 4;
  while(!flux.eof())
  {
    flux >> f1 >> f2 >> f3;
    g1->SetPoint(i,i*5./25.,f1);
    g1->SetTitle("Scalar Number Flux;a*;Number Flux");
    g2->SetPoint(i,i*5./25.,f2);
    g2->SetTitle("Spinor Number Flux;a*;Number Flux");
    g3->SetPoint(i,i*5./25.,f3);
    g3->SetTitle("Vector Number Flux;a*;Number Flux");
    ++i;
  }
  flux.close();

  ifstream fluxke("data_files/cfluxke_n2.dat");
  TGraph* CFLUX2S0K = new TGraph();
  CFLUX2S0K->SetTitle(Form("Scalar Flux a* = %f;K;Flux",1./5.*a1)); 
  TGraph* CFLUX2S1K = new TGraph(); 
  CFLUX2S1K->SetTitle(Form("Spinor Flux a* = %f;K;Flux",1./5.*a2)); 
  TGraph* CFLUX2S2K = new TGraph(); 
  CFLUX2S2K->SetTitle(Form("Vector Flux a* = %f;K;Flux",1./5.*a3)); 
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
  TGraph *CFLUX2S0KE = new TGraph();
  TGraph *CFLUX2S1KE = new TGraph();
  TGraph *CFLUX2S2KE = new TGraph();
  TGraph *TOTALFLUX = new TGraph();
  
  for(int ma=0; ma <= 25; ++ma)
  {
    for(int k=0; k <= 168; ++k)
    {
      for(int e=0; e <= 100; ++e)
      {
        fluxke >> dummy;
        if(k==0 && ma==a1 && e!=100)
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
        if(k==2 && ma==a1 && e!=100)
        {
           cfluxke = dummy;
           CFLUX2S1KE->SetPoint(e,(e+1)/20.,cfluxke);
        }
      }
    }
  }
  double sumFlux[99];

  for(int ma=0; ma <= 25; ++ma)
  {
    for(int k=0; k <= 119; ++k)
    {
      for(int e=0; e <= 100; ++e)
      {
        fluxke >> dummy;
        if(ma==a1 && e!=100)
        {
        	sumFlux[e] += dummy;
        }	
        if(k==2 && ma==a1 && e!=100)
        {
          cfluxke = dummy;
          CFLUX2S2KE->SetPoint(e,(e+1)/20.,cfluxke);
        }
        if(ma==a1 && e==99)
        {
          cfluxkeMax = dummy;
          //cout << k << "   " << cfluxkeMax << endl; 
        }
      }
    }
  }
  fluxke.close();
  for(int e=0; e <=99; e++)
  {
  	TOTALFLUX->SetPoint(e,(e+1)/20.,sumFlux[e]);
  }
  
  g1->SetLineColor(kRed);
  g2->SetLineColor(kBlue);
  g3->SetLineColor(kGreen);
  
  TCanvas *c = new TCanvas("c","c",500,500);
  //c->SetLogy();
  g3->Draw("al");
  g2->Draw("same");
  g1->Draw("same");
  TLegend *l = new TLegend(0.6, 0.6, 0.9, 0.9);
  l->SetFillStyle(0);
  l->SetBorderSize(0);
  l->AddEntry(g1,"spin 0","l"); 
  l->AddEntry(g2,"spin 1/2","l"); 
  l->AddEntry(g3,"spin 1","l");
  l->Draw();
//  TCanvas *c2 = new TCanvas("c2","c2",500,500);
  CFLUX2S0K->SetLineColor(kRed);
  CFLUX2S1K->SetLineColor(kBlue);
  CFLUX2S2K->SetLineColor(kGreen);
  CFLUX2S0KE->SetLineColor(kRed);
  CFLUX2S1KE->SetLineColor(kBlue);
  CFLUX2S2KE->SetLineColor(kGreen);
//  CFLUX2S0KE->Draw("ALP"); 
//  TCanvas *c3 = new TCanvas("c3","c3",500,500);
//  CFLUX2S1K->Draw("ALP"); 
  TCanvas *c4 = new TCanvas("c4","c4",500,500);
  CFLUX2S2K->Draw("ALP"); 
//  TCanvas *c5 = new TCanvas("c5","c5",500,500);
//  CFLUX2S0KE->Draw("ALP");
//  TCanvas *c6 = new TCanvas("c6","c6",500,500);
//  CFLUX2S1KE->Draw("ALP");
  TCanvas *c7 = new TCanvas("c7","c7",500,500);
  CFLUX2S2KE->Draw("ALP");
  TCanvas *c8 = new TCanvas("c8","c8",500,500);
  TOTALFLUX->Draw("ALP");
  
}
