void cfactor()
{
  double nu1 = -0.473;
  double nu2 = -0.473;

  const double kL = 11.3*TMath::Pi();

  double cFactor = pow((1.+2*nu1)*(1.+2*nu2),0.5)/(3+nu1+nu2)*exp(kL*(1+nu1+nu2))/pow((exp(kL*(1.+2*nu1))-1.)*(exp(kL*(1.+2*nu2))-1.),0.5);

  cout << (1.+2*nu1)*(1.+2*nu2) << endl;
  cout << cFactor << endl;
}
