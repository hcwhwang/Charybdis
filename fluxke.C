void fluxke()
{
  double  dummy, value;
  int a0=0;
  int a1=0;
  int a2=0;

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
 
  int n=2;
  ifstream flux(Form("data_files/fluxke_n%i.dat",n));
  TGraph *FLUX2S0KE = new TGraph();
  FLUX2S0KE->SetLineColor(kRed);
  FLUX2S0KE->SetLineWidth(3);
  FLUX2S0KE->SetTitle(Form("Scalar D=%i,a*=%f,j=%i,m=%i;#omega r_{h};Flux",n+4,1./5.*a0,j0,m0)); 

  TGraph *FLUX2S1KE = new TGraph();
  FLUX2S1KE->SetLineColor(kBlue);
  FLUX2S1KE->SetLineWidth(3);
  FLUX2S1KE->SetTitle(Form("Spinor D=%i,a*=%f,j=%i,m=%i;#omega r_{h};Flux",n+4,1./5.*a1,j1,m1)); 

  TGraph *FLUX2S2KE = new TGraph();
  FLUX2S2KE->SetLineColor(kGreen);
  FLUX2S2KE->SetLineWidth(3);
  FLUX2S2KE->SetTitle(Form("Vector D=%i,a*=%f,j=%i,m=%i;#omega r_{h};Flux",n+4,1./5.*a2,j2,m2)); 

  TGraph *TOTALFLUX = new TGraph();
  TOTALFLUX->SetTitle(Form("Total D=%i,a*=%f;#omega r_{h};Flux",n+4,1./5.*a2)); 
  TOTALFLUX->SetLineWidth(3);

  TGraph *SCALARFLUX = new TGraph();
  SCALARFLUX->SetTitle(Form("Scalar D=%i,a*=%f;#omega r_{h};Flux",n+4,1./5.*a2)); 
  SCALARFLUX->SetLineColor(kRed);
  SCALARFLUX->SetLineWidth(3);

  TGraph *SPINORFLUX = new TGraph();
  SPINORFLUX->SetTitle(Form("Spinor D=%i,a*=%f;#omega r_{h};Flux",n+4,1./5.*a2)); 
  SPINORFLUX->SetLineColor(kBlue);
  SPINORFLUX->SetLineWidth(3);

  TGraph *VECTORFLUX = new TGraph();
  VECTORFLUX->SetTitle(Form("Vector D=%i,a*=%f;#omega r_{h};Flux",n+4,1./5.*a2)); 
  VECTORFLUX->SetLineColor(kGreen);
  VECTORFLUX->SetLineWidth(3);

  double sumScalarFlux[101]={0.};
  double sumSpinorFlux[101]={0.};
  double sumVectorFlux[101]={0.};

  for(int ma=0; ma <= 25; ++ma)
  {
    for(int k=0; k <= 168; ++k)
    {
      for(int e=0; e <= 102; ++e)
      {
        flux >> dummy;
        if(ma==a0 && e!=101 && e!=102)
        {
        	sumScalarFlux[e] += dummy;
        }
        if(k==k0 && ma==a0 && e!=102 && e!=101)
        {
          value = dummy;
          FLUX2S0KE->SetPoint(e,(e)/20.,value);
        }
      }
    }
  }
  for(int ma=0; ma <= 25; ++ma)
  {
    for(int k=0; k <= 155; ++k)
    {
      for(int e=0; e <= 102; ++e)
      {
        flux >> dummy;
        if(ma==a1 && e!=101 && e!=102)
        {
        	sumSpinorFlux[e] += dummy;
        }
        if(k==k1 && ma==a1 && e!=102 && e!=101)
        {
           value = dummy;
           FLUX2S1KE->SetPoint(e,(e)/20.,value);
        }
      }
    }
  }
  for(int ma=0; ma <= 25; ++ma)
  {
    for(int k=0; k <= 119; ++k)
    {
      for(int e=0; e <= 102; ++e)
      {
        flux >> dummy;
        if(ma==a2 && e!=101 && e!=102)
        {
        	sumVectorFlux[e] += dummy;
        }
        if(k==k2 && ma==a2 && e!=101 && e!=102)
        {
          value = dummy;
          FLUX2S2KE->SetPoint(e,(e)/20.,value);
        }
      }
    }
  }
  for(int e=0; e <=100; ++e)
  {
    SCALARFLUX->SetPoint(e,(e)/20.,sumScalarFlux[e]);
    SPINORFLUX->SetPoint(e,(e)/20.,sumSpinorFlux[e]);
    VECTORFLUX->SetPoint(e,(e)/20.,sumVectorFlux[e]);
    TOTALFLUX->SetPoint(e,(e)/20.,sumVectorFlux[e]+sumSpinorFlux[e]+sumScalarFlux[e]);
  }
  
  flux.close();
  TCanvas *c5 = new TCanvas("c5","c5",500,500);
  FLUX2S0KE->Draw("AL");
  TCanvas *c6 = new TCanvas("c6","c6",500,500);
  FLUX2S1KE->Draw("AL");
  TCanvas *c7 = new TCanvas("c7","c7",500,500);
  FLUX2S2KE->Draw("AL");
  TCanvas *c8 = new TCanvas("c8","c8",500,500);
  SCALARFLUX->Draw("AL");
  TCanvas *c9 = new TCanvas("c9","c9",500,500);
  SPINORFLUX->Draw("AL");
  TCanvas *c10 = new TCanvas("c10","c10",500,500);
  VECTORFLUX->Draw("AL");
  TCanvas *c11 = new TCanvas("c11","c11",500,500);
  TOTALFLUX->Draw("AL");
}
