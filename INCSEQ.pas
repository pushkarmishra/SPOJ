program INCSEQ;
var
    bitdp: Array[1..51, 1..131073] of longint;
    N, K, in1, i: integer; temp, idx, j: longint;
    MAX: longint;
 
Function update(k: integer; idx, val:longint): integer;
Begin
    while (idx <= MAX) do begin
        bitdp[k][idx]:= (bitdp[k][idx]+val);
        idx:= idx+ (idx and -idx);
    end;
End;
 
Function sum(k: integer; idx: longint): longint;
var
    ans: longint;
Begin
    ans :=0;
    while (idx > 0) do begin
        ans:= (bitdp[k][idx]+ans);
        idx:= idx- (idx and -idx);
    end;
    exit(ans);
End;
 
BEGIN
    MAX:= 131072;
    readln(N, K);
    while (N>0) and (K>0) do Begin
        for i:= 1 to N do
        Begin
            if (i=N) then readln(in1)
            else read(in1);
            for j:= 1 to K do
            begin
                if (j=1) then update(j, in1, 1)
                else begin
                    temp:= sum(j-1, in1-1);
                    update(j, in1, temp);
                end;
            end;
        End;
        writeln(bitdp[K][MAX]);
 
        FillChar(bitdp, SizeOf(bitdp), 0);
        readln(N, K);
    End;
END.
