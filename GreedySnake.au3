#cs ----------------------------------------------------------------------------

	AutoIt Version: 3.3.2.0
	Author:raoyi

	Script Function:
	Game of Greedy Snake

#ce ----------------------------------------------------------------------------
#include <StaticConstants.au3>
#include <ButtonConstants.au3>
#include <GUIConstantsEx.au3>
#include <WindowsConstants.au3>

Global Const $WIDTH = 15, $HIGHT = 15, $LenBody = 13 ; 定义游戏界面大小
Global Const $UP = 1, $DOWN = -1, $LEFT = -2, $RIGHT = 2 ; 定义4个方向, 为了方便理解
Global $Dir = $RIGHT ; 初始化移动方向
Global $dTime = 300 ; 每移动一步需要的时间, 可通过这个变量改变速度
Global $idSnake[$WIDTH * $HIGHT][3] ; $idSnake[n][0,1,2]: 第n节body的 ID / x坐标 / y坐标
Global $nTail ; 标志蛇的尾巴.
Global $nHead ; 标志蛇的头
Global $LenSnake ; 蛇的长度
Global $xHead ; 头的x坐标
Global $yHead ; 头的y坐标
Global $idDou ; 豆豆的ID
Global $iValue[$HIGHT][$WIDTH] ; 可移动区域的值 0:可移动 / 1:蛇的身体 / 2:豆豆

HotKeySet("^!x", "debug") ; for debug

$hGUI = GUICreate("", $WIDTH * $LenBody, $HIGHT * $LenBody, -1, -1, $WS_POPUP + $WS_BORDER, $WS_EX_LAYERED, GUICreate("")) ;弹出式+细边框 / 分层
GUISetBkColor(0x888888)
$KeyUp = GUICtrlCreateButton("&w", 200, 200, 10, 10)
GUICtrlSetState(-1, $Gui_Hide)
$KeyDown = GUICtrlCreateButton("&s", 200, 200, 10, 10)
GUICtrlSetState(-1, $Gui_Hide)
$KeyLeft = GUICtrlCreateButton("&a", 200, 200, 10, 10)
GUICtrlSetState(-1, $Gui_Hide)
$KeyRight = GUICtrlCreateButton("&d", 200, 200, 10, 10)
GUICtrlSetState(-1, $Gui_Hide)
_API_SetLayeredWindowAttributes($hGUI, 0x888888)
;DllCall("user32.dll", "str", "SetParent", "HWnd", $hGUI, "HWnd", WinGetHandle("Program Manager"))

GUISetState()

InitGame()
CreateDouDou()

While 1
	$Dir = GetDir()
	move($Dir)
WEnd

Func CreateDouDou()
	Do
		$i = Random(0, $HIGHT - 1, 1)
		$j = Random(0, $WIDTH - 1, 1)
	Until $iValue[$i][$j] <> 1
	$iValue[$i][$j] = 2
	$idDou = GUICtrlCreateLabel("", $j * $LenBody, $i * $LenBody, $LenBody - 1, $LenBody - 1, 0x0201, $GUI_WS_EX_PARENTDRAG)
	GUICtrlSetBkColor(-1, 0xF9732B)
EndFunc   ;==>CreateDouDou

Func GetDir()
	$start = TimerInit()
	While TimerDiff($start) < $dTime
		If Not WinActive($hGUI) Then
			GUISetBkColor(0x888888)
			WinWaitActive($hGUI) ; 不激活状态暂停
		EndIf
		Switch GUIGetMsg() ; 判断按键是否和当前方向冲突
			Case -3
				Exit
			Case $KeyUp
				If Abs($Dir) <> 1 Then Return $UP
			Case $KeyDown
				If Abs($Dir) <> 1 Then Return $DOWN
			Case $KeyLeft
				If Abs($Dir) <> 2 Then Return $LEFT
			Case $KeyRight
				If Abs($Dir) <> 2 Then Return $RIGHT
		EndSwitch
	WEnd
	Return $Dir
EndFunc   ;==>GetDir

Func move($direction)
	UpdateHeadxy($direction)
	Switch $iValue[$yHead / $LenBody][$xHead / $LenBody]
		Case 0 ; 可移动
			GUICtrlSetPos($idSnake[$nTail][0], $xHead, $yHead)
			GUICtrlSetBkColor($idSnake[$nHead][0], 0x00FF00)

			$iValue[$idSnake[$nTail][2] / $LenBody][$idSnake[$nTail][1] / $LenBody] = 0
			$iValue[$yHead / $LenBody][$xHead / $LenBody] = 1

			$idSnake[$nTail][1] = $xHead
			$idSnake[$nTail][2] = $yHead

			$nHead = $nTail
			GUICtrlSetBkColor($idSnake[$nHead][0], 0x00aa00)
			If $nTail = $LenSnake - 1 Then
				$nTail = 0
			Else
				$nTail += 1
			EndIf
		Case 1 ; 碰到身体, 挂了
			MsgBox(0, "Game Over", "Game Over" & @LF & "You bite yourself")
			Exit
		Case 2 ; 碰到豆豆, 我吃
			GUICtrlSetBkColor($idSnake[$nHead][0], 0x00FF00)
			For $i = $LenSnake To $nTail + 1 Step -1
				$idSnake[$i][0] = $idSnake[$i - 1][0]
				$idSnake[$i][1] = $idSnake[$i - 1][1]
				$idSnake[$i][2] = $idSnake[$i - 1][2]
			Next
			$idSnake[$nTail][0] = $idDou
			GUICtrlSetBkColor($idDou, 0x00aa00)
			$nHead = $nTail
			$idSnake[$nTail][1] = $xHead
			$idSnake[$nTail][2] = $yHead
			$iValue[$yHead / $LenBody][$xHead / $LenBody] = 1
			$nTail += 1
			$LenSnake += 1
			CreateDouDou()
	EndSwitch
EndFunc   ;==>move

Func UpdateHeadxy($direction)
	Switch $direction
		Case $UP
			If $yHead = 0 Then ; 到达区域顶端
				$yHead = $LenBody * ($HIGHT - 1)
			Else
				$yHead -= $LenBody
			EndIf
		Case $DOWN
			If $yHead = $LenBody * ($HIGHT - 1) Then ; 到达区域底端
				$yHead = 0
			Else
				$yHead += $LenBody
			EndIf
		Case $LEFT
			If $xHead = 0 Then ; 到达区域左端
				$xHead = $LenBody * ($WIDTH - 1)
			Else
				$xHead -= $LenBody
			EndIf
		Case $RIGHT
			If $xHead = $LenBody * ($WIDTH - 1) Then ; 到达区域右端
				$xHead = 0
			Else
				$xHead += $LenBody
			EndIf
	EndSwitch
EndFunc   ;==>UpdateHeadxy

Func InitGame()
	For $i = 0 To $HIGHT - 1
		For $j = 0 To $WIDTH - 1
			$iValue[$i][$j] = 0
		Next
	Next

	For $i = 0 To 2
		$idSnake[$i][0] = GUICtrlCreateLabel("", $LenBody * $i, 0, $LenBody - 1, $LenBody - 1, 0x0201, $GUI_WS_EX_PARENTDRAG)
		GUICtrlSetBkColor(-1, 0x00FF00)
		$idSnake[$i][1] = $i * $LenBody
		$idSnake[$i][2] = 0
		$iValue[0][$i] = 1
	Next
	GUICtrlSetBkColor(-1, 0x00aa00)
	$xHead = ($i - 1) * $LenBody
	$yHead = 0
	$nTail = 0
	$nHead = $i - 1
	$LenSnake = $i
	;_API_SetLayeredWindowAttributes($hGUI, 0x00ff00)
EndFunc   ;==>InitGame

Func _API_SetLayeredWindowAttributes($hwnd, $i_transcolor, $Transparency = 255, $isColorRef = False)
	Local Const $AC_SRC_ALPHA = 1
	Local Const $ULW_ALPHA = 2
	Local Const $LWA_ALPHA = 0x2
	Local Const $LWA_COLORKEY = 0x1
	If Not $isColorRef Then
		$i_transcolor = Hex(String($i_transcolor), 6)
		$i_transcolor = Execute('0x00' & StringMid($i_transcolor, 5, 2) & StringMid($i_transcolor, 3, 2) & StringMid($i_transcolor, 1, 2))
	EndIf
	Local $Ret = DllCall("user32.dll", "int", "SetLayeredWindowAttributes", "hwnd", $hwnd, "long", $i_transcolor, "byte", $Transparency, "long", $LWA_COLORKEY + $LWA_ALPHA)
	Select
		Case @error
			Return SetError(@error, 0, 0)
		Case $Ret[0] = 0
			Return SetError(4, 0, 0)
		Case Else
			Return 1
	EndSelect
EndFunc   ;==>_API_SetLayeredWindowAttributes

Func debug()
	$msg = ""
	For $i = 0 To $HIGHT - 1
		For $j = 0 To $WIDTH - 1
			$msg &= $iValue[$i][$j] & " "
		Next
		$msg &= @LF
	Next
	MsgBox(0, "", $msg)
EndFunc   ;==>debug
