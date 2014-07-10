void fluxke()
{
  double  dummy, value;
  int a1=7;
  ifstream flux("data_files/fluxke_n2.dat");
  TGraph *FLUX2S0KE = new TGraph();
  TGraph *FLUX2S1KE = new TGraph();
  TGraph *FLUX2S2KE = new TGraph();

  for(int ma=0; ma <= 25; ++ma)
  {
    for(int k=0; k <= 168; ++k)
    {
      for(int e=0; e <= 102; ++e)
      {
        flux >> dummy;
        if(k==169 && ma==a1 && e!=102 && e!=101)
        {
          value = dummy;
          FLUX2S0KE->SetPoint(e,(e)/20.,value*e/20.);
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
        if(k==2 && ma==a1 && e!=102 && e!=101)
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
        if(k==2 && ma==a1 && e!=101 && e!=102)
        {
          value = dummy;
          FLUX2S2KE->SetPoint(e,(e)/20.,value);
        }
      }
    }
  }
  flux.close();
  TCanvas *c5 = new TCanvas("c5","c5",500,500);
  FLUX2S0KE->Draw("ALP");
  TCanvas *c6 = new TCanvas("c6","c6",500,500);
  FLUX2S1KE->Draw("ALP");
  TCanvas *c7 = new TCanvas("c7","c7",500,500);
  FLUX2S2KE->Draw("ALP");

}
