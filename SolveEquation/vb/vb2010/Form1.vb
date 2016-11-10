Option Strict Off
Option Explicit On
Friend Class Form1
	Inherits System.Windows.Forms.Form
	
    Private Declare Function SolveEquation Lib "SolveEquationDll.dll" (ByRef z As Double, ByRef x As Double) As Integer
	
    Private Sub txtR0_TextChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles txtR0.TextChanged
        Call OnTextChange()
    End Sub
	
    Private Sub txtI0_TextChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles txtI0.TextChanged
        Call OnTextChange()
    End Sub
	
    Private Sub txtR1_TextChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles txtR1.TextChanged
        Call OnTextChange()
    End Sub
	
    Private Sub txtI1_TextChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles txtI1.TextChanged
        Call OnTextChange()
    End Sub
	
    Private Sub txtR2_TextChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles txtR2.TextChanged
        Call OnTextChange()
    End Sub
	
    Private Sub txtI2_TextChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles txtI2.TextChanged
        Call OnTextChange()
    End Sub
	
    Private Sub txtR3_TextChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles txtR3.TextChanged
        Call OnTextChange()
    End Sub
	
    Private Sub txtI3_TextChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles txtI3.TextChanged
        Call OnTextChange()
    End Sub
	
    Private Sub txtR4_TextChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles txtR4.TextChanged
        Call OnTextChange()
    End Sub
	
    Private Sub txtI4_TextChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles txtI4.TextChanged
        Call OnTextChange()
    End Sub
	
	Private Sub OnTextChange()
		Dim z(10) As Double
		On Error Resume Next
		z(0) = CDbl(txtR0.Text)
		z(1) = CDbl(txtI0.Text)
		z(2) = CDbl(txtR1.Text)
		z(3) = CDbl(txtI1.Text)
		z(4) = CDbl(txtR2.Text)
		z(5) = CDbl(txtI2.Text)
		z(6) = CDbl(txtR3.Text)
		z(7) = CDbl(txtI3.Text)
		z(8) = CDbl(txtR4.Text)
		z(9) = CDbl(txtI4.Text)
		Dim x(12) As Double
		Dim n As Integer '有效解的个数
        n = SolveEquation(z(0), x(0)) '解方程
		Dim d As Double
		d = 0.0000000001
		If n >= 1 Then
			txtRA.Text = CStr(x(0))
			txtIA.Text = CStr(x(1))
            lblA.Text = x(2).ToString("0.e+000")
            If System.Math.Abs(x(2)) > d Then
                lblA.ForeColor = System.Drawing.Color.Red
            Else
                lblA.ForeColor = System.Drawing.Color.Blue
            End If
		Else
			txtRA.Text = ""
			txtIA.Text = ""
            lblA.Text = ""
		End If
		If n >= 2 Then
			txtRB.Text = CStr(x(3))
			txtIB.Text = CStr(x(4))
            lblB.Text = x(5).ToString("0.e+000")
			If System.Math.Abs(x(5)) > d Then
				lblB.ForeColor = System.Drawing.Color.Red
			Else
				lblB.ForeColor = System.Drawing.Color.Blue
			End If
		Else
			txtRB.Text = ""
			txtIB.Text = ""
            lblB.Text = ""
        End If
		If n >= 3 Then
			txtRC.Text = CStr(x(6))
			txtIC.Text = CStr(x(7))
            lblC.Text = x(8).ToString("0.e+000")
			If System.Math.Abs(x(8)) > d Then
				lblC.ForeColor = System.Drawing.Color.Red
			Else
				lblC.ForeColor = System.Drawing.Color.Blue
			End If
		Else
			txtRC.Text = ""
			txtIC.Text = ""
            lblC.Text = ""
        End If
		If n >= 4 Then
			txtRD.Text = CStr(x(9))
			txtID.Text = CStr(x(10))
            lblD.Text = x(11).ToString("0.e+000")
			If System.Math.Abs(x(11)) > d Then
				lblD.ForeColor = System.Drawing.Color.Red
			Else
				lblD.ForeColor = System.Drawing.Color.Blue
			End If
		Else
			txtRD.Text = ""
			txtID.Text = ""
            lblD.Text = ""
        End If
	End Sub
End Class