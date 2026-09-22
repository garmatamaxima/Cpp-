
## AUTOHOTKEY скрипт для komorebic який додає клавіші швидкого доступу

Alt це ! 
shift це +
ctrl це ^ 

###### Назви layout

"BSP" "VerticalStack" "HorizontalStack" "UltrawideVerticalStack" "Rows" "Grid" "RightMainVerticalStack"

###### Кастомний конфіг  komorebi.json

{
  "$schema": "https://raw.githubusercontent.com/LGUG2Z/komorebi/v0.1.39/schema.json",
  "app_specific_configuration_path": "$Env:USERPROFILE/applications.json",
  "window_hiding_behaviour": "Cloak",
  "cross_monitor_move_behaviour": "Insert",
  "default_workspace_padding": 2,
  "default_container_padding": 2,
  "border": true,
  "border-implementation": "Native",
  "boarder_style": "System",
  "border_width": 2,
  "border_offset": 0,
  "boarder_colors": {
    "single": "#e8e8e3",
    "stack": "#e8e8e3",
    "floating": "#e8e8e3",
    "monocle": "#e8e8e3",
    "unfocused": "#e8e8e3"
  },
  "mouse_follows_focus": false,
  "transparency": true,
  "transparency_alpha": 248,
  "animation": {
    "enabled": true,
    "duration": 220,
    "fps": 60,
    "style": {
      "movement": "EaseOutExpo",
      "transparency": "Linear"
    }
  },
  "theme": {
    "palette": "Catppuccin",
    "name": "Mocha",
    "accent": "Mocha"
  },
  "stackbar": {
    "height": 24,
    "mode": "Never",
    "label": "Title",
    "tabs": {
      "width": 200,
      "font_size": 16
    }
  },
  "monitors": [
    {
      "workspaces": [
        {
          "name": "I",
          "layout": "RightMainVerticalStack"
        },
        {
          "name": "II",
          "layout": "Scrolling",
          "workspace_padding": 3,
          "container_padding": 3
        },
        {
          "name": "III",
          "layout": "Grid",
          "workspace_padding": 10,
          "container_padding": 3
        },
        {
          "name": "IV",
          "layout": "Rows"
        },
        {
          "name": "V",
          "layout": "Rows"
        },
        {
          "name": "VI",
          "layout": "Grid"
        }
      ]
    }
  ]
}

###### Стандартні клавіші швидкого доступу Autohotkey
```

#Requires AutoHotkey v2.0.2
#SingleInstance Force

Komorebic(cmd) {
    RunWait(format("komorebic.exe {}", cmd), , "Hide")
}

!q::Komorebic("close")
!m::Komorebic("minimize")

; Focus windows
!h::Komorebic("focus left")
!j::Komorebic("focus down")
!k::Komorebic("focus up")
!l::Komorebic("focus right")

!+[::Komorebic("cycle-focus previous")
!+]::Komorebic("cycle-focus next")

; Move windows
!+h::Komorebic("move left")
!+j::Komorebic("move down")
!+k::Komorebic("move up")
!+l::Komorebic("move right")

; Stack windows
!Left::Komorebic("stack left")
!Down::Komorebic("stack down")
!Up::Komorebic("stack up")
!Right::Komorebic("stack right")
!;::Komorebic("unstack")
![::Komorebic("cycle-stack previous")
!]::Komorebic("cycle-stack next")

; Resize
!=::Komorebic("resize-axis horizontal increase")
!-::Komorebic("resize-axis horizontal decrease")
!+=::Komorebic("resize-axis vertical increase")
!+_::Komorebic("resize-axis vertical decrease")

; Manipulate windows
!t::Komorebic("toggle-float")
!f::Komorebic("toggle-monocle")

; Window manager options
!+r::Komorebic("retile")
!p::Komorebic("toggle-pause")

; Layouts
!x::Komorebic("flip-layout horizontal")
!y::Komorebic("flip-layout vertical")

; Workspaces
!1::Komorebic("focus-workspace 0")
!2::Komorebic("focus-workspace 1")
!3::Komorebic("focus-workspace 2")
!4::Komorebic("focus-workspace 3")
!5::Komorebic("focus-workspace 4")
!6::Komorebic("focus-workspace 5")
!7::Komorebic("focus-workspace 6")
!8::Komorebic("focus-workspace 7")

; Move windows across workspaces
!+1::Komorebic("move-to-workspace 0")
!+2::Komorebic("move-to-workspace 1")
!+3::Komorebic("move-to-workspace 2")
!+4::Komorebic("move-to-workspace 3")
!+5::Komorebic("move-to-workspace 4")
!+6::Komorebic("move-to-workspace 5")
!+7::Komorebic("move-to-workspace 6")
!+8::Komorebic("move-to-workspace 7")`
```
