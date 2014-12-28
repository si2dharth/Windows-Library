Public Class Form1
    Dim R As New Random()

    Private Sub Timer1_Tick(sender As Object, e As EventArgs) Handles Timer1.Tick
        Graph1.AddReading(R.Next(100))
    End Sub
End Class
