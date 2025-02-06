object SpeakerSetupForm: TSpeakerSetupForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Speaker Setup'
  ClientHeight = 434
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
  object SpeakerGroupBox: TGroupBox
    Left = 8
    Top = 6
    Width = 154
    Height = 392
    Caption = ' Speaker setup '
    TabOrder = 0
    object SpeakerCheckBox0: TCheckBox
      Left = 9
      Top = 17
      Width = 89
      Height = 17
      Caption = 'Front left/right'
      TabOrder = 0
      OnClick = SpeakerCheckBoxClick
    end
    object SpeakerCheckBox1: TCheckBox
      Tag = 1
      Left = 9
      Top = 34
      Width = 126
      Height = 17
      Caption = 'Low frequency effects'
      TabOrder = 1
      OnClick = SpeakerCheckBoxClick
    end
    object SpeakerCheckBox2: TCheckBox
      Tag = 2
      Left = 9
      Top = 51
      Width = 78
      Height = 17
      Caption = 'Front center'
      TabOrder = 2
      OnClick = SpeakerCheckBoxClick
    end
    object SpeakerCheckBox3: TCheckBox
      Tag = 3
      Left = 9
      Top = 68
      Width = 86
      Height = 17
      Caption = 'Rear left/right'
      TabOrder = 3
      OnClick = SpeakerCheckBoxClick
    end
    object SpeakerCheckBox4: TCheckBox
      Tag = 4
      Left = 9
      Top = 85
      Width = 75
      Height = 17
      Caption = 'Rear center'
      TabOrder = 4
      OnClick = SpeakerCheckBoxClick
    end
    object SpeakerCheckBox5: TCheckBox
      Tag = 5
      Left = 9
      Top = 102
      Width = 123
      Height = 17
      Caption = 'Front left/right center'
      TabOrder = 5
      OnClick = SpeakerCheckBoxClick
    end
    object SpeakerCheckBox6: TCheckBox
      Tag = 6
      Left = 9
      Top = 119
      Width = 120
      Height = 17
      Caption = 'Rear left/right center'
      TabOrder = 6
      OnClick = SpeakerCheckBoxClick
    end
    object SpeakerCheckBox7: TCheckBox
      Tag = 7
      Left = 9
      Top = 136
      Width = 114
      Height = 17
      Caption = 'Front left/right wide'
      TabOrder = 7
      OnClick = SpeakerCheckBoxClick
    end
    object SpeakerCheckBox8: TCheckBox
      Tag = 8
      Left = 9
      Top = 153
      Width = 108
      Height = 17
      Caption = 'Top front left/right'
      TabOrder = 8
      OnClick = SpeakerCheckBoxClick
    end
    object SpeakerCheckBox9: TCheckBox
      Tag = 9
      Left = 9
      Top = 170
      Width = 70
      Height = 17
      Caption = 'Top center'
      TabOrder = 9
      OnClick = SpeakerCheckBoxClick
    end
    object SpeakerCheckBox10: TCheckBox
      Tag = 10
      Left = 9
      Top = 187
      Width = 97
      Height = 17
      Caption = 'Top front center'
      TabOrder = 10
      OnClick = SpeakerCheckBoxClick
    end
    object Speaker20Button: TButton
      Left = 8
      Top = 362
      Width = 42
      Height = 21
      Caption = 'Stereo'
      TabOrder = 20
      OnClick = Speaker20ButtonClick
    end
    object Speaker51Button: TButton
      Left = 50
      Top = 362
      Width = 27
      Height = 21
      Caption = '5.1'
      TabOrder = 21
      OnClick = Speaker51ButtonClick
    end
    object Speaker71Button: TButton
      Left = 77
      Top = 362
      Width = 27
      Height = 21
      Caption = '7.1'
      TabOrder = 22
      OnClick = Speaker71ButtonClick
    end
    object SpeakerResetButton: TButton
      Left = 104
      Top = 362
      Width = 42
      Height = 21
      Caption = 'Reset'
      TabOrder = 23
      OnClick = SpeakerResetButtonClick
    end
    object SpeakerCheckBox11: TCheckBox
      Tag = 11
      Left = 9
      Top = 204
      Width = 109
      Height = 17
      Caption = 'Left/right surround'
      TabOrder = 11
      OnClick = SpeakerCheckBoxClick
    end
    object SpeakerCheckBox12: TCheckBox
      Tag = 12
      Left = 9
      Top = 221
      Width = 135
      Height = 17
      Caption = 'Low frequency effects 2'
      TabOrder = 12
      OnClick = SpeakerCheckBoxClick
    end
    object SpeakerCheckBox13: TCheckBox
      Tag = 13
      Left = 9
      Top = 238
      Width = 95
      Height = 17
      Caption = 'Top back center'
      TabOrder = 13
      OnClick = SpeakerCheckBoxClick
    end
    object SpeakerCheckBox14: TCheckBox
      Tag = 14
      Left = 9
      Top = 255
      Width = 83
      Height = 17
      Caption = 'Side left/right'
      TabOrder = 14
      OnClick = SpeakerCheckBoxClick
    end
    object SpeakerCheckBox15: TCheckBox
      Tag = 15
      Left = 9
      Top = 272
      Width = 103
      Height = 17
      Caption = 'Top side left/right'
      TabOrder = 15
      OnClick = SpeakerCheckBoxClick
    end
    object SpeakerCheckBox16: TCheckBox
      Tag = 16
      Left = 9
      Top = 289
      Width = 106
      Height = 17
      Caption = 'Top back left/right'
      TabOrder = 16
      OnClick = SpeakerCheckBoxClick
    end
    object SpeakerCheckBox17: TCheckBox
      Tag = 17
      Left = 9
      Top = 306
      Width = 113
      Height = 17
      Caption = 'Bottom front center'
      TabOrder = 17
      OnClick = SpeakerCheckBoxClick
    end
    object SpeakerCheckBox18: TCheckBox
      Tag = 18
      Left = 9
      Top = 323
      Width = 124
      Height = 17
      Caption = 'Bottom front left/right'
      TabOrder = 18
      OnClick = SpeakerCheckBoxClick
    end
    object SpeakerCheckBox19: TCheckBox
      Tag = 19
      Left = 9
      Top = 340
      Width = 127
      Height = 17
      Caption = 'Top left/right surround'
      TabOrder = 19
      OnClick = SpeakerCheckBoxClick
    end
  end
  object FormOKButton: TButton
    Left = 7
    Top = 404
    Width = 75
    Height = 23
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 1
  end
  object FormCancelButton: TButton
    Left = 88
    Top = 404
    Width = 75
    Height = 23
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 2
  end
end
