object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 462
  ClientWidth = 900
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Slika: TImage
    Left = 8
    Top = 8
    Width = 721
    Height = 409
    OnMouseDown = SlikaMouseDown
  end
  object Prost_Poligon: TButton
    Left = 8
    Top = 427
    Width = 75
    Height = 25
    Caption = 'Prost_Poligon'
    TabOrder = 0
    OnMouseDown = Prost_PoligonMouseDown
  end
  object editBrojTacaka: TEdit
    Left = 753
    Top = 8
    Width = 112
    Height = 21
    TabOrder = 1
    Text = '5'
  end
  object generisiTacke: TButton
    Left = 752
    Top = 48
    Width = 113
    Height = 25
    Caption = 'generisiTacke'
    TabOrder = 2
    OnMouseDown = generisiTackeMouseDown
  end
  object GiftWrapping: TButton
    Left = 89
    Top = 427
    Width = 112
    Height = 25
    Caption = 'GiftWrapping'
    TabOrder = 3
    OnMouseDown = GiftWrappingMouseDown
  end
  object GrahamScan: TButton
    Left = 207
    Top = 427
    Width = 106
    Height = 25
    Caption = 'Graham-Scan'
    TabOrder = 4
    OnMouseDown = GrahamScanMouseDown
  end
  object pripadnostKonveksnom: TRadioButton
    Left = 735
    Top = 88
    Width = 157
    Height = 17
    Caption = 'u konveksnom/tangenta'
    TabOrder = 5
  end
  object dodavanjeTacki: TRadioButton
    Left = 735
    Top = 128
    Width = 157
    Height = 17
    Caption = 'Dodavanje tacki'
    TabOrder = 6
  end
  object Button1: TButton
    Left = 735
    Top = 232
    Width = 113
    Height = 25
    Caption = 'Generisi krugove'
    TabOrder = 7
    OnClick = Button1Click
  end
  object sweepLineKruznice: TButton
    Left = 319
    Top = 429
    Width = 113
    Height = 25
    Caption = 'Kruznice - pogresno'
    TabOrder = 8
    OnClick = sweepLineKruzniceClick
  end
  object crtajKrugove: TRadioButton
    Left = 735
    Top = 161
    Width = 113
    Height = 17
    Caption = 'Crtaj krugove'
    TabOrder = 9
  end
  object kdTree: TButton
    Left = 438
    Top = 429
    Width = 89
    Height = 25
    Caption = 'KD tree'
    TabOrder = 10
    OnClick = kdTreeClick
  end
  object crtajPravougaonik: TRadioButton
    Left = 735
    Top = 200
    Width = 113
    Height = 17
    Caption = 'Crtaj pravougaonik'
    TabOrder = 11
  end
  object rangeTree: TButton
    Left = 533
    Top = 429
    Width = 75
    Height = 25
    Caption = 'Range tree'
    TabOrder = 12
    OnClick = rangeTreeClick
  end
  object kruzniceSweepLineTacno: TButton
    Left = 614
    Top = 429
    Width = 115
    Height = 25
    Caption = 'Sweep line kruznice'
    TabOrder = 13
    OnClick = kruzniceSweepLineTacnoClick
  end
end
