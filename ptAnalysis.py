#!/usr/bin/env python

from xml.dom.minidom import parse
import sys, os

from ROOT import *

inputFile1 = sys.argv[1]
inputFile2 = sys.argv[2]

file1 = TFile.Open(inputFile1)
file2 = TFile.Open(inputFile2)

hPtFrame = TH1F("hPtFrame", "Pt;P_{T}(GeV/c);Events",100, 0, 3000)
hScalarPtFrame = TH1F("hScalarPtFrame", "Scalar P_{T};P_{T}(GeV/c);Events",100, 0, 3000)
hSpinorPtFrame = TH1F("hSpinorPtFrame", "Spinor P_{T};P_{T}(GeV/c);Events",100, 0, 3000)
hVectorPtFrame = TH1F("hVectorPtFrame", "Vector P_{T};P_{T}(GeV/c);Events",100, 0, 3000)
hBhMassFrame = TH1F("hBhMassFrame", "Blackhole Mass;mass(GeV/c^{2});Events",100, 5000, 10000)
hEnergyFrame = TH1F("hEnergyFrame", "Energy;#omega;Events",100, 0, 5000)

hLowDBhMass = TH1F("hLowDBhMass", "Low Dimension Mass;mass(GeV/c^{2});Events",100, 5000, 10000)
hLowDPt = TH1F("hLowDPt", "Low Dimension Pt;P_{T}(GeV/c);Events",100, 0, 3000)
hLowDEnergy = TH1F("hLowDE", "Low Dimension Energy;#omega;Events",100, 0, 5000)
hLowDBhMass = file1.Get("hBhIniMass")
hLowDBhMass.SetTitle("6D")
hLowDBhMass.SetLineColor(kBlue)

hLowDPt = file1.Get("hPt")
hLowDPt.SetTitle("6D")
hLowDPt.SetLineColor(kBlue)

hLowDScalarPt = file1.Get("hPtScalar")
hLowDScalarPt.SetTitle("6D")
hLowDScalarPt.SetLineColor(kBlue)

hLowDSpinorPt = file1.Get("hPtSpinor")
hLowDSpinorPt.SetTitle("6D")
hLowDSpinorPt.SetLineColor(kBlue)

hLowDVectorPt = file1.Get("hPtVector")
hLowDVectorPt.SetTitle("6D")
hLowDVectorPt.SetLineColor(kBlue)

hLowDEnergy = file1.Get("hEnergy")
hLowDEnergy.SetTitle("6D")
hLowDEnergy.SetLineColor(kBlue)


hHighBhMass = TH1F("hHighBhMass", "High Dimension Mass;mass(GeV/c^{2});Events",100, 5000, 10000)
hHighDPt = TH1F("hHighDPt", "High Dimension Pt;P_{T}(GeV/c);Events",100, 0, 3000)
hHighDEnergy = TH1F("hHighDE", "High Dimension Energy;#omega;Events",100, 0, 5000)
hLowDBhMass = file1.Get("hBhIniMass")
hLowDBhMass.SetTitle("6D")
hLowDBhMass.SetLineColor(kBlue)

hHighDPt = file2.Get("hPt")
hHighDPt.SetTitle("10D")
hHighDPt.SetLineColor(kRed)

hHighDScalarPt = file2.Get("hPtScalar")
hHighDScalarPt.SetTitle("10D")
hHighDScalarPt.SetLineColor(kRed)

hHighDSpinorPt = file2.Get("hPtSpinor")
hHighDSpinorPt.SetTitle("10D")
hHighDSpinorPt.SetLineColor(kRed)

hHighDVectorPt = file2.Get("hPtVector")
hHighDVectorPt.SetTitle("10D")
hHighDVectorPt.SetLineColor(kRed)

hHighDBhMass = file2.Get("hBhIniMass")
hHighDBhMass.SetTitle("10D")
hHighDBhMass.SetLineColor(kRed)

hHighDEnergy = file2.Get("hEnergy")
hHighDEnergy.SetTitle("10D")
hHighDEnergy.SetLineColor(kRed)

hPtSet = hLowDPt, hHighDPt
hScalarPtSet = hLowDScalarPt, hHighDScalarPt
hSpinorPtSet = hLowDSpinorPt, hHighDSpinorPt
hVectorPtSet = hLowDVectorPt, hHighDVectorPt
hEnergySet = hLowDEnergy, hHighDEnergy
legPt = TLegend(0.65, 0.65, 0.9, 0.9)
legPt.SetFillStyle(0)
legPt.SetBorderSize(0)
c1 = TCanvas("c1","c1",500,500)
c1.SetLogy()

for h in hPtSet:
  h.Scale(1/(h.Integral()))

hPtFrame.SetMaximum(max(h.GetMaximum() for h in hPtSet)*1.2)
hPtFrame.Draw()

for h in hPtSet:
  h.Draw("same")
  legPt.AddEntry(h, h.GetTitle(), "l")
legPt.Draw()

hBhMassSet = hLowDBhMass, hHighDBhMass
legBhMass = TLegend(0.65, 0.65, 0.9, 0.9)
legBhMass.SetFillStyle(0)
legBhMass.SetBorderSize(0)
c2 = TCanvas("c2","c2",500,500)
c2.SetLogy()
hBhMassFrame.SetMaximum(max(h.GetMaximum() for h in hBhMassSet)*1.2)
hBhMassFrame.Draw()
for h in hBhMassSet:
  h.Draw("same")
  legBhMass.AddEntry(h, h.GetTitle(), "l")
legBhMass.Draw()

#Scalar Pt
legScalarPt = TLegend(0.65, 0.65, 0.9, 0.9)
legScalarPt.SetFillStyle(0)
legScalarPt.SetBorderSize(0)
c3 = TCanvas("c3","c3",500,500)
c3.SetLogy()

for h in hScalarPtSet:
  h.Scale(1/(h.Integral()))

hScalarPtFrame.SetMaximum(max(h.GetMaximum() for h in hPtSet)*1.2)
hScalarPtFrame.Draw()

for h in hScalarPtSet:
  h.Draw("same")
  legScalarPt.AddEntry(h, h.GetTitle(), "l")
legScalarPt.Draw()

#Spinor Pt
legSpinorPt = TLegend(0.65, 0.65, 0.9, 0.9)
legSpinorPt.SetFillStyle(0)
legSpinorPt.SetBorderSize(0)
c4 = TCanvas("c4","c4",500,500)
c4.SetLogy()

for h in hSpinorPtSet:
  h.Scale(1/(h.Integral()))

hSpinorPtFrame.SetMaximum(max(h.GetMaximum() for h in hSpinorPtSet)*1.2)
hSpinorPtFrame.Draw()

for h in hSpinorPtSet:
  h.Draw("same")
  legSpinorPt.AddEntry(h, h.GetTitle(), "l")
legSpinorPt.Draw()

#Vector Pt
legVectorPt = TLegend(0.65, 0.65, 0.9, 0.9)
legVectorPt.SetFillStyle(0)
legVectorPt.SetBorderSize(0)
c5 = TCanvas("c5","c5",500,500)
c5.SetLogy()

for h in hVectorPtSet:
  h.Scale(1/(h.Integral()))

hVectorPtFrame.SetMaximum(max(h.GetMaximum() for h in hVectorPtSet)*1.2)
hVectorPtFrame.Draw()

for h in hVectorPtSet:
  h.Draw("same")
  legVectorPt.AddEntry(h, h.GetTitle(), "l")
legVectorPt.Draw()

#Energy
legEnergy = TLegend(0.65, 0.65, 0.9, 0.9)
legEnergy.SetFillStyle(0)
legEnergy.SetBorderSize(0)
c6 = TCanvas("c6","c6",500,500)
c6.SetLogy()

for h in hEnergySet:
  h.Scale(1/(h.Integral()))

hEnergyFrame.SetMaximum(max(h.GetMaximum() for h in hEnergySet)*1.2)
hEnergyFrame.Draw()

for h in hEnergySet:
  h.Draw("same")
  legEnergy.AddEntry(h, h.GetTitle(), "l")
legEnergy.Draw()


