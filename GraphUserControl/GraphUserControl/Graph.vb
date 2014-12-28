Public Class Graph

    Private YValues As New List(Of Integer)
    Private Origin As Point

    Private _Step As Integer = 1
    Public Property GraphStep() As Integer
        Get
            Return _Step
        End Get
        Set(ByVal value As Integer)
            _Step = value
        End Set
    End Property

    Private _Range As Point
    Public Property Range() As Point
        Get
            Return _Range
        End Get
        Set(ByVal value As Point)
            _Range = value
        End Set
    End Property

    Enum GraphScrollType
        OverWrite
        Move
    End Enum

    Private _GraphType As GraphScrollType = GraphScrollType.OverWrite
    Public Property GraphType() As GraphScrollType
        Get
            Return _GraphType
        End Get
        Set(ByVal value As GraphScrollType)
            _GraphType = value
        End Set
    End Property


    Private G As System.Drawing.Graphics
    Private CurrentStep As Integer = 0

    Private Sub Graph_Load(sender As Object, e As EventArgs) Handles Me.Load
        G = GraphPanel.CreateGraphics
        Origin = New Point(GraphPanel.Width / 10, GraphPanel.Height * 0.9)
    End Sub

    Public Sub New()

        ' This call is required by the designer.
        InitializeComponent()
        ' Add any initialization after the InitializeComponent() call.

    End Sub

    Private Sub DrawAxis()
        G.DrawLine(Pens.Black, Origin.X, Origin.Y, GraphPanel.Width, Origin.Y)
        G.DrawLine(Pens.Black, Origin.X, Origin.Y, Origin.X, 0)
    End Sub

    Private Sub ScrollGraph()
        G.Clear(Color.White)
        DrawAxis()
        Dim OldY As Integer = YValues(0) * Origin.Y / Range.Y
        Dim PixelStep As Integer = GraphStep * (GraphPanel.Width - Origin.X) / Range.X
        For i = 1 To YValues.Count - 1
            Dim NewY As Integer = YValues(i) * Origin.Y / Range.Y
            Dim X As Integer = GraphPanel.Width - (CurrentStep - i + 1) * PixelStep
            If X >= Origin.X Then G.DrawLine(Pens.Black, X, Origin.Y - OldY, X + PixelStep, Origin.Y - NewY)
            OldY = NewY
        Next
    End Sub

    Private Sub OverWrite()
        If YValues.Count < 2 Then Return

        Dim PixelStep As Integer = GraphStep * (GraphPanel.Width - Origin.X) / Range.X
        Dim Cursor As Integer = Origin.X + CurrentStep * PixelStep Mod (GraphPanel.Width - Origin.X)

        Dim ErasePen = New Pen(Brushes.White, PixelStep)
        G.DrawLine(ErasePen, Origin.X + ((Cursor + 5) Mod (GraphPanel.Width - Origin.X)), 0, Origin.X + ((Cursor + 5) Mod (GraphPanel.Width - Origin.X)), Origin.Y - 1)

        Dim OldY As Integer = YValues(YValues.Count - 2) * Origin.Y / Range.Y
        Dim NewY As Integer = YValues(YValues.Count - 1) * Origin.Y / Range.Y
        'X = Origin.X + CurrentStep Mod (Range.X / GraphStep)
        G.DrawLine(Pens.Black, Cursor, Origin.Y - OldY, Cursor + PixelStep, Origin.Y - NewY)
    End Sub

    Public Sub Initialize()
        G.Clear(Color.White)
        DrawAxis()
    End Sub

    Public Sub AddReading(x As Integer)
        CurrentStep += 1
        YValues.Add(x)
        If GraphType = GraphScrollType.Move Then
            ScrollGraph()
        Else
            OverWrite()
        End If

    End Sub
End Class
