object HDMI2SupportForm: THDMI2SupportForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'HDMI 2.x Support'
  ClientHeight = 432
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
  object TMDSRateGroupBox: TGroupBox
    Left = 8
    Top = 6
    Width = 154
    Height = 50
    Caption = ' TMDS character rate '
    TabOrder = 0
    object TMDSRateLabel: TLabel
      Left = 115
      Top = 22
      Width = 23
      Height = 13
      Caption = 'Mcsc'
    end
    object OverrideTMDSRate: TCheckBox
      Left = 9
      Top = 21
      Width = 66
      Height = 17
      Caption = 'Maximum:'
      TabOrder = 0
      OnClick = OverrideTMDSRateClick
    end
    object TMDSRate: TEdit
      Left = 79
      Top = 19
      Width = 30
      Height = 21
      MaxLength = 4
      TabOrder = 1
      OnChange = TMDSRateChange
      OnExit = TMDSRateExit
    end
  end
  object FeaturesGroupBox: TGroupBox
    Left = 8
    Top = 61
    Width = 154
    Height = 144
    Caption = ' Features '
    TabOrder = 1
    object FeaturesCheckBox7: TCheckBox
      Tag = 7
      Left = 9
      Top = 17
      Width = 85
      Height = 17
      Caption = 'SCDC present'
      TabOrder = 0
      OnClick = FeaturesCheckBoxClick
    end
    object FeaturesCheckBox6: TCheckBox
      Tag = 6
      Left = 9
      Top = 34
      Width = 123
      Height = 17
      Caption = 'Read request capable'
      TabOrder = 1
      OnClick = FeaturesCheckBoxClick
    end
    object FeaturesCheckBox4: TCheckBox
      Tag = 4
      Left = 9
      Top = 51
      Width = 125
      Height = 17
      Caption = 'Content bpc indication'
      TabOrder = 2
      OnClick = FeaturesCheckBoxClick
    end
    object FeaturesCheckBox3: TCheckBox
      Tag = 3
      Left = 9
      Top = 68
      Width = 126
      Height = 17
      Caption = '<= 340 Mcsc scramble'
      TabOrder = 3
      OnClick = FeaturesCheckBoxClick
    end
    object FeaturesCheckBox2: TCheckBox
      Tag = 2
      Left = 9
      Top = 85
      Width = 105
      Height = 17
      Caption = 'Independent view'
      TabOrder = 4
      OnClick = FeaturesCheckBoxClick
    end
    object FeaturesCheckBox1: TCheckBox
      Tag = 1
      Left = 9
      Top = 102
      Width = 64
      Height = 17
      Caption = 'Dual view'
      TabOrder = 5
      OnClick = FeaturesCheckBoxClick
    end
    object FeaturesCheckBox0: TCheckBox
      Left = 9
      Top = 119
      Width = 99
      Height = 17
      Caption = '3D OSD disparity'
      TabOrder = 6
      OnClick = FeaturesCheckBoxClick
    end
  end
  object ColorFormatsGroupBox: TGroupBox
    Left = 8
    Top = 210
    Width = 154
    Height = 76
    Caption = ' YCbCr 4:2:0 deep color '
    TabOrder = 2
    object ColorFormatsCheckBox0: TCheckBox
      Left = 9
      Top = 17
      Width = 89
      Height = 17
      Caption = '30-bit (10 bpc)'
      TabOrder = 0
      OnClick = ColorFormatsCheckBoxClick
    end
    object ColorFormatsCheckBox1: TCheckBox
      Tag = 1
      Left = 9
      Top = 34
      Width = 89
      Height = 17
      Caption = '36-bit (12 bpc)'
      TabOrder = 1
      OnClick = ColorFormatsCheckBoxClick
    end
    object ColorFormatsCheckBox2: TCheckBox
      Tag = 2
      Left = 9
      Top = 51
      Width = 89
      Height = 17
      Caption = '48-bit (16 bpc)'
      TabOrder = 2
      OnClick = ColorFormatsCheckBoxClick
    end
  end
  object RefreshRateGroupBox: TGroupBox
    Left = 8
    Top = 291
    Width = 154
    Height = 105
    Caption = ' Variable refresh rate '
    TabOrder = 3
    object VRateLabel: TLabel
      Left = 9
      Top = 22
      Width = 35
      Height = 13
      Caption = 'Range:'
    end
    object VRateDash: TShape
      Left = 74
      Top = 29
      Width = 6
      Height = 1
      Brush.Color = clWindowText
      Pen.Color = clWindowText
    end
    object HzLabel: TLabel
      Left = 121
      Top = 22
      Width = 12
      Height = 13
      Caption = 'Hz'
    end
    object MinVRate: TEdit
      Left = 48
      Top = 19
      Width = 21
      Height = 21
      MaxLength = 2
      TabOrder = 0
      OnChange = MinVRateChange
      OnExit = MinVRateExit
    end
    object MaxVRate: TEdit
      Left = 85
      Top = 19
      Width = 30
      Height = 21
      MaxLength = 4
      TabOrder = 1
      OnChange = MaxVRateChange
      OnExit = MaxVRateExit
    end
    object Features21CheckBox5: TCheckBox
      Tag = 5
      Left = 9
      Top = 46
      Width = 53
      Height = 17
      Caption = 'M delta'
      TabOrder = 2
      OnClick = Features21CheckBoxClick
    end
    object Features21CheckBox4: TCheckBox
      Tag = 4
      Left = 9
      Top = 63
      Width = 76
      Height = 17
      Caption = 'Cinema VRR'
      TabOrder = 3
      OnClick = Features21CheckBoxClick
    end
    object Features21CheckBox3: TCheckBox
      Tag = 3
      Left = 9
      Top = 80
      Width = 95
      Height = 17
      Caption = 'Negative M VRR'
      TabOrder = 4
      OnClick = Features21CheckBoxClick
    end
  end
  object FRLRateGroupBox: TGroupBox
    Left = 170
    Top = 6
    Width = 154
    Height = 50
    Caption = ' Maximum FRL rate '
    TabOrder = 4
    object FRLRateComboBox: TComboBox
      Left = 9
      Top = 19
      Width = 136
      Height = 21
      Style = csDropDownList
      DropDownCount = 25
      ItemHeight = 13
      TabOrder = 0
      OnChange = FRLRateComboBoxChange
    end
  end
  object Features21GroupBox: TGroupBox
    Left = 170
    Top = 61
    Width = 154
    Height = 76
    Caption = ' 2.1 features '
    TabOrder = 5
    object Features21CheckBox2: TCheckBox
      Tag = 2
      Left = 9
      Top = 17
      Width = 77
      Height = 17
      Caption = 'Fast Vactive'
      TabOrder = 0
      OnClick = Features21CheckBoxClick
    end
    object Features21CheckBox1: TCheckBox
      Tag = 1
      Left = 9
      Top = 34
      Width = 128
      Height = 17
      Caption = 'Auto low-latency mode'
      TabOrder = 1
      OnClick = Features21CheckBoxClick
    end
    object Features21CheckBox0: TCheckBox
      Left = 9
      Top = 51
      Width = 110
      Height = 17
      Caption = 'FAPA start location'
      TabOrder = 2
      OnClick = Features21CheckBoxClick
    end
  end
  object DSCGroupBox: TGroupBox
    Left = 170
    Top = 142
    Width = 154
    Height = 254
    Caption = ' Display stream compression '
    TabOrder = 6
    object DSCFRLRateLabel: TLabel
      Left = 9
      Top = 129
      Width = 92
      Height = 13
      Caption = 'Maximum FRL rate:'
    end
    object DSCSlicesLabel: TLabel
      Left = 9
      Top = 177
      Width = 76
      Height = 13
      Caption = 'Maximum slices:'
    end
    object DSCChunkSizeLabel: TLabel
      Left = 9
      Top = 226
      Width = 80
      Height = 13
      Caption = 'Max chunk total:'
    end
    object DSCChunkSizeUnitsLabel: TLabel
      Left = 120
      Top = 226
      Width = 11
      Height = 13
      Caption = 'kB'
    end
    object DSCCheckBox7: TCheckBox
      Tag = 7
      Left = 9
      Top = 17
      Width = 63
      Height = 17
      Caption = 'DSC 1.2a'
      TabOrder = 0
      OnClick = DSCCheckBoxClick
    end
    object DSCCheckBox6: TCheckBox
      Tag = 6
      Left = 9
      Top = 34
      Width = 77
      Height = 17
      Caption = 'YCbCr 4:2:0'
      TabOrder = 1
      OnClick = DSCCheckBoxClick
    end
    object DSCCheckBox0: TCheckBox
      Left = 9
      Top = 51
      Width = 89
      Height = 17
      Caption = '30-bit (10 bpc)'
      TabOrder = 2
      OnClick = DSCCheckBoxClick
    end
    object DSCCheckBox1: TCheckBox
      Tag = 1
      Left = 9
      Top = 68
      Width = 89
      Height = 17
      Caption = '36-bit (12 bpc)'
      TabOrder = 3
      OnClick = DSCCheckBoxClick
    end
    object DSCCheckBox2: TCheckBox
      Tag = 2
      Left = 9
      Top = 85
      Width = 89
      Height = 17
      Caption = '48-bit (16 bpc)'
      TabOrder = 4
      OnClick = DSCCheckBoxClick
    end
    object DSCCheckBox3: TCheckBox
      Tag = 3
      Left = 9
      Top = 102
      Width = 50
      Height = 17
      Caption = 'All bpp'
      TabOrder = 5
      OnClick = DSCCheckBoxClick
    end
    object DSCFRLRateComboBox: TComboBox
      Left = 9
      Top = 146
      Width = 136
      Height = 21
      Style = csDropDownList
      DropDownCount = 25
      ItemHeight = 13
      TabOrder = 6
      OnChange = DSCFRLRateComboBoxChange
    end
    object DSCSlicesComboBox: TComboBox
      Left = 9
      Top = 194
      Width = 136
      Height = 21
      Style = csDropDownList
      DropDownCount = 25
      ItemHeight = 13
      TabOrder = 7
      OnChange = DSCSlicesComboBoxChange
    end
    object DSCChunkSize: TEdit
      Left = 93
      Top = 223
      Width = 21
      Height = 21
      MaxLength = 2
      TabOrder = 8
      OnChange = DSCChunkSizeChange
      OnExit = DSCChunkSizeExit
    end
  end
  object FormOKButton: TButton
    Left = 169
    Top = 402
    Width = 75
    Height = 23
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 7
  end
  object FormCancelButton: TButton
    Left = 250
    Top = 402
    Width = 75
    Height = 23
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 8
  end
end
