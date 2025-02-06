object HDRStaticMetadataForm: THDRStaticMetadataForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'HDR Static Metadata'
  ClientHeight = 287
  ClientWidth = 170
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
  object EOTFGroupBox: TGroupBox
    Left = 8
    Top = 6
    Width = 154
    Height = 93
    Caption = ' Transfer functions '
    TabOrder = 0
    object EOTFCheckBox0: TCheckBox
      Left = 9
      Top = 17
      Width = 135
      Height = 17
      Caption = 'Traditional gamma - SDR'
      TabOrder = 0
      OnClick = EOTFCheckBoxClick
    end
    object EOTFCheckBox1: TCheckBox
      Tag = 1
      Left = 9
      Top = 34
      Width = 136
      Height = 17
      Caption = 'Traditional gamma - HDR'
      TabOrder = 1
      OnClick = EOTFCheckBoxClick
    end
    object EOTFCheckBox2: TCheckBox
      Tag = 2
      Left = 9
      Top = 51
      Width = 92
      Height = 17
      Caption = 'SMPTE ST 2084'
      TabOrder = 2
      OnClick = EOTFCheckBoxClick
    end
    object EOTFCheckBox3: TCheckBox
      Tag = 3
      Left = 9
      Top = 68
      Width = 108
      Height = 17
      Caption = 'Hybrid Log-Gamma'
      TabOrder = 3
      OnClick = EOTFCheckBoxClick
    end
  end
  object TypeGroupBox: TGroupBox
    Left = 8
    Top = 104
    Width = 154
    Height = 42
    Caption = ' Static metadata '
    TabOrder = 1
    object TypeCheckBox0: TCheckBox
      Left = 9
      Top = 17
      Width = 52
      Height = 17
      Caption = 'Type 1'
      TabOrder = 0
      OnClick = TypeCheckBoxClick
    end
  end
  object LuminanceGroupBox: TGroupBox
    Left = 8
    Top = 151
    Width = 154
    Height = 100
    Caption = ' Luminance '
    TabOrder = 2
    object LuminanceLabel0: TLabel
      Left = 9
      Top = 22
      Width = 74
      Height = 13
      Caption = 'Max luminance:'
    end
    object LuminanceLabel1: TLabel
      Left = 9
      Top = 47
      Width = 77
      Height = 13
      Caption = 'Max frame-avg:'
    end
    object LuminanceLabel2: TLabel
      Left = 9
      Top = 72
      Width = 70
      Height = 13
      Caption = 'Min luminance:'
    end
    object Luminance0: TEdit
      Left = 90
      Top = 19
      Width = 24
      Height = 21
      MaxLength = 3
      TabOrder = 0
      OnChange = LuminanceChange
      OnExit = LuminanceExit
    end
    object Luminance1: TEdit
      Tag = 1
      Left = 90
      Top = 44
      Width = 24
      Height = 21
      MaxLength = 3
      TabOrder = 1
      OnChange = LuminanceChange
      OnExit = LuminanceExit
    end
    object Luminance2: TEdit
      Tag = 2
      Left = 90
      Top = 69
      Width = 24
      Height = 21
      MaxLength = 3
      TabOrder = 2
      OnChange = LuminanceChange
      OnExit = LuminanceExit
    end
  end
  object FormOKButton: TButton
    Left = 7
    Top = 257
    Width = 75
    Height = 23
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 3
  end
  object FormCancelButton: TButton
    Left = 88
    Top = 257
    Width = 75
    Height = 23
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 4
  end
end
