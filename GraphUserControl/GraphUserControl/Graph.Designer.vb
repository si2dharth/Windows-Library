<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Graph
    Inherits System.Windows.Forms.UserControl

    'UserControl overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.GraphPanel = New System.Windows.Forms.Panel()
        Me.SuspendLayout()
        '
        'GraphPanel
        '
        Me.GraphPanel.Dock = System.Windows.Forms.DockStyle.Fill
        Me.GraphPanel.Location = New System.Drawing.Point(0, 0)
        Me.GraphPanel.Name = "GraphPanel"
        Me.GraphPanel.Size = New System.Drawing.Size(303, 312)
        Me.GraphPanel.TabIndex = 0
        '
        'Graph
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.Controls.Add(Me.GraphPanel)
        Me.Name = "Graph"
        Me.Size = New System.Drawing.Size(303, 312)
        Me.ResumeLayout(False)

    End Sub
    Friend WithEvents GraphPanel As System.Windows.Forms.Panel

End Class
