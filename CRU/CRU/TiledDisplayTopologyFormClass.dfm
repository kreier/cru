object TiledDisplayTopologyForm: TTiledDisplayTopologyForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Tiled Display Topology'
  ClientHeight = 368
  ClientWidth = 332
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object TopologyIDGroupBox: TGroupBox
    Left = 8
    Top = 6
    Width = 154
    Height = 100
    Caption = ' Topology ID '
    TabOrder = 0
    object VendorIDLabel: TLabel
      Left = 9
      Top = 22
      Width = 52
      Height = 13
      Caption = 'Vendor ID:'
    end
    object ProductIDLabel: TLabel
      Left = 9
      Top = 47
      Width = 55
      Height = 13
      Caption = 'Product ID:'
    end
    object SerialIDLabel: TLabel
      Left = 9
      Top = 72
      Width = 54
      Height = 13
      Caption = 'ID serial #:'
    end
    object VendorID: TEdit
      Left = 68
      Top = 19
      Width = 77
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 6
      TabOrder = 0
      OnChange = VendorIDChange
      OnExit = VendorIDExit
    end
    object ProductID: TEdit
      Left = 68
      Top = 44
      Width = 77
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 4
      TabOrder = 1
      OnChange = ProductIDChange
      OnExit = ProductIDExit
    end
    object SerialID: TEdit
      Left = 68
      Top = 69
      Width = 77
      Height = 21
      MaxLength = 10
      TabOrder = 2
      OnChange = SerialIDChange
      OnExit = SerialIDExit
    end
  end
  object PhysicalEnclosuresGroupBox: TGroupBox
    Left = 8
    Top = 111
    Width = 154
    Height = 59
    Caption = ' Physical display enclosures '
    TabOrder = 1
    object PhysicalEnclosuresRadioButton1: TRadioButton
      Tag = 1
      Left = 9
      Top = 17
      Width = 46
      Height = 17
      Caption = 'Single'
      TabOrder = 0
      OnClick = EnclosuresRadioButtonClick
    end
    object PhysicalEnclosuresRadioButton0: TRadioButton
      Left = 9
      Top = 34
      Width = 54
      Height = 17
      Caption = 'Multiple'
      TabOrder = 1
      OnClick = EnclosuresRadioButtonClick
    end
  end
  object SingleTileBehaviorGroupBox: TGroupBox
    Left = 8
    Top = 175
    Width = 154
    Height = 93
    Caption = ' Single-tile behavior '
    TabOrder = 2
    object SingleTileBehaviorRadioButton1: TRadioButton
      Tag = 1
      Left = 9
      Top = 17
      Width = 117
      Height = 17
      Caption = 'Displayed at location'
      TabOrder = 0
      OnClick = SingleTileBehaviorRadioButtonClick
    end
    object SingleTileBehaviorRadioButton2: TRadioButton
      Tag = 2
      Left = 9
      Top = 34
      Width = 111
      Height = 17
      Caption = 'Scaled to fit display'
      TabOrder = 1
      OnClick = SingleTileBehaviorRadioButtonClick
    end
    object SingleTileBehaviorRadioButton3: TRadioButton
      Tag = 3
      Left = 9
      Top = 51
      Width = 115
      Height = 17
      Caption = 'Cloned to other tiles'
      TabOrder = 2
      OnClick = SingleTileBehaviorRadioButtonClick
    end
    object SingleTileBehaviorRadioButton0: TRadioButton
      Left = 9
      Top = 68
      Width = 46
      Height = 17
      Caption = 'Other'
      TabOrder = 3
      OnClick = SingleTileBehaviorRadioButtonClick
    end
  end
  object MultipleTileBehaviorGroupBox: TGroupBox
    Left = 8
    Top = 273
    Width = 154
    Height = 59
    Caption = ' Multiple-tile behavior '
    TabOrder = 3
    object MultipleTileBehaviorRadioButton1: TRadioButton
      Tag = 1
      Left = 9
      Top = 17
      Width = 117
      Height = 17
      Caption = 'Displayed at location'
      TabOrder = 0
      OnClick = MultipleTileBehaviorRadioButtonClick
    end
    object MultipleTileBehaviorRadioButton0: TRadioButton
      Left = 9
      Top = 34
      Width = 46
      Height = 17
      Caption = 'Other'
      TabOrder = 1
      OnClick = MultipleTileBehaviorRadioButtonClick
    end
  end
  object TilesGroupBox: TGroupBox
    Left = 170
    Top = 6
    Width = 154
    Height = 50
    Caption = ' Number of tiles '
    TabOrder = 4
    object TilesLabel: TLabel
      Left = 34
      Top = 22
      Width = 6
      Height = 13
      Caption = 'x'
    end
    object HTiles: TEdit
      Left = 9
      Top = 19
      Width = 21
      Height = 21
      MaxLength = 2
      TabOrder = 0
      OnChange = HTilesChange
      OnExit = HTilesExit
    end
    object VTiles: TEdit
      Left = 44
      Top = 19
      Width = 21
      Height = 21
      MaxLength = 2
      TabOrder = 1
      OnChange = VTilesChange
      OnExit = VTilesExit
    end
  end
  object LocationGroupBox: TGroupBox
    Left = 170
    Top = 61
    Width = 154
    Height = 50
    Caption = ' Tile location '
    TabOrder = 5
    object LocationLabel: TLabel
      Left = 34
      Top = 22
      Width = 4
      Height = 13
      Caption = ','
    end
    object HLocation: TEdit
      Left = 9
      Top = 19
      Width = 21
      Height = 21
      MaxLength = 2
      TabOrder = 0
      OnChange = HLocationChange
      OnExit = HLocationExit
    end
    object VLocation: TEdit
      Left = 44
      Top = 19
      Width = 21
      Height = 21
      MaxLength = 2
      TabOrder = 1
      OnChange = VLocationChange
      OnExit = VLocationExit
    end
  end
  object SizeGroupBox: TGroupBox
    Left = 170
    Top = 116
    Width = 154
    Height = 50
    Caption = ' Tile size '
    TabOrder = 6
    object SizeLabel: TLabel
      Left = 49
      Top = 22
      Width = 6
      Height = 13
      Caption = 'x'
    end
    object HSize: TEdit
      Left = 9
      Top = 19
      Width = 36
      Height = 21
      MaxLength = 5
      TabOrder = 0
      OnChange = HSizeChange
      OnExit = HSizeExit
    end
    object VSize: TEdit
      Left = 59
      Top = 19
      Width = 36
      Height = 21
      MaxLength = 5
      TabOrder = 1
      OnChange = VSizeChange
      OnExit = VSizeExit
    end
  end
  object BezelGroupBox: TGroupBox
    Left = 170
    Top = 171
    Width = 154
    Height = 161
    Caption = ' Bezel size in pixels '
    TabOrder = 7
    object MultiplierLabel: TLabel
      Left = 15
      Top = 22
      Width = 46
      Height = 13
      Caption = 'Multiplier:'
    end
    object MultiplierDivisorLabel: TLabel
      Left = 95
      Top = 22
      Width = 19
      Height = 13
      Caption = '/ 10'
    end
    object Rectangle: TShape
      Left = 19
      Top = 56
      Width = 116
      Height = 87
      Pen.Width = 4
    end
    object PixelMultiplier: TEdit
      Left = 65
      Top = 19
      Width = 24
      Height = 21
      MaxLength = 3
      TabOrder = 0
      OnChange = PixelMultiplierChange
      OnExit = PixelMultiplierExit
    end
    object TopBezelSize: TEdit
      Left = 65
      Top = 48
      Width = 24
      Height = 21
      MaxLength = 3
      TabOrder = 1
      OnChange = TopBezelSizeChange
      OnExit = TopBezelSizeExit
    end
    object LeftBezelSize: TEdit
      Left = 9
      Top = 89
      Width = 24
      Height = 21
      MaxLength = 3
      TabOrder = 2
      OnChange = LeftBezelSizeChange
      OnExit = LeftBezelSizeExit
    end
    object RightBezelSize: TEdit
      Left = 121
      Top = 89
      Width = 24
      Height = 21
      MaxLength = 3
      TabOrder = 3
      OnChange = RightBezelSizeChange
      OnExit = RightBezelSizeExit
    end
    object BottomBezelSize: TEdit
      Left = 65
      Top = 130
      Width = 24
      Height = 21
      MaxLength = 3
      TabOrder = 4
      OnChange = BottomBezelSizeChange
      OnExit = BottomBezelSizeExit
    end
  end
  object FormOKButton: TButton
    Left = 169
    Top = 338
    Width = 75
    Height = 23
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 8
  end
  object FormCancelButton: TButton
    Left = 250
    Top = 338
    Width = 75
    Height = 23
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 9
  end
end
