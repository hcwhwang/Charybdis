#!/usr/bin/env python

from xml.dom.minidom import parse
import sys, os

from ROOT import *

#inputFile1 = sys.argv[1]
#inputFile2 = sys.argv[2]

file1 = TFile.Open("event_ADD_6D_13TeV_10000.root")
file2 = TFile.Open("event_ADD_7D_13TeV_10000.root")
file3 = TFile.Open("event_ADD_8D_13TeV_10000.root")
file4 = TFile.Open("event_ADD_9D_13TeV_10000.root")
file5 = TFile.Open("event_ADD_10D_13TeV_10000.root")

hPtFrame = TH1F("hPtFrame", "Pt;P_{T}(GeV/c);Events",100, 0, 3000)

h6DPt = TH1F("h6DPt", "Low Dimension Pt;P_{T}(GeV/c);Events",100, 0, 3000)
h6DPt = file1.Get("hPt")
h6DPt.SetTitle("6D")
h6DPt.SetLineColor(kBlue)

h7DPt = TH1F("h7DPt", "Low Dimension Pt;P_{T}(GeV/c);Events",100, 0, 3000)
h7DPt = file2.Get("hPt")
h7DPt.SetTitle("7D")
h7DPt.SetLineColor(kRed)

h8DPt = TH1F("h8DPt", "Low Dimension Pt;P_{T}(GeV/c);Events",100, 0, 3000)
h8DPt = file3.Get("hPt")
h8DPt.SetTitle("8D")
h8DPt.SetLineColor(kGreen)

h9DPt = TH1F("h9DPt", "Low Dimension Pt;P_{T}(GeV/c);Events",100, 0, 3000)
h9DPt = file4.Get("hPt")
h9DPt.SetTitle("9D")
h9DPt.SetLineColor(kMagenta)

h10DPt = TH1F("h10DPt", "Low Dimension Pt;P_{T}(GeV/c);Events",100, 0, 3000)
h10DPt = file5.Get("hPt")
h10DPt.SetTitle("10D")
h10DPt.SetLineColor(kBlack)

hSet = h6DPt,h7DPt,h8DPt,h9DPt,h10DPt
legPt = TLegend(0.65, 0.65, 0.9, 0.9)
legPt.SetFillStyle(0)
legPt.SetBorderSize(0)
c1 = TCanvas("c1","c1",500,500)
c1.SetLogy()
#hPtFrame.SetMaximum(max(h.GetMaximum() for h in hSet)*10)
#hPtFrame.SetMaximum(0.2)

for h in hSet:
  h.Scale(1/(h.Integral()))

#hPtFrame.SetMinimum(1e-09)
hPtFrame.SetMaximum(max(h.GetMaximum() for h in hSet)*1.2)
hPtFrame.Draw()

for h in hSet:
  h.Draw("same")
  legPt.AddEntry(h, h.GetTitle(), "l")
legPt.Draw()

