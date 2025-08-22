class Grid:
    def __init__(self,start):
        self.start=start
        self.n=len(start)
        
    def testgoal(self,r,c):
        
        #if(self.start[0][0]!=0 or self.start[self.n-1][self.n-1]!=0):
           # return False
       # return True
        return r==self.n-1 and c==self.n-1
    
    def movegen(self,r,c):
        directions=[(0,1),(0,-1),(1,0),(-1,0),(-1,-1),(1,1),(-1,1),(1,-1)]
        moves=[]
        for i,j in directions:
            ni,nj=r+i,c+j
            if 0<=ni<self.n and 0<=nj<self.n and self.start[ni][nj]==0:
                moves.append((ni,nj));
        return moves 
    def __str__(self):
        return "\n".join(" ".join(str(x) for x in row) for row in self.start)

def hewristic(r,c,n):
    #matix order-1-row+matrix order-1-col
    return abs(n-1-r)+abs(n-1-c);
    

    
def best_first_search(start):
    if start.start[0][0] != 0 or start.start[start.n-1][start.n-1] != 0:
        return 0, "Path does not exist"
    OPEN=[(0,0,hewristic(0,0,start.n),1,[(0,0)])]
    CLOSED=[]
    while OPEN:
        OPEN.sort(key=lambda x:x[2])
        r,c,h,l,path=OPEN.pop(0)
        
        if start.testgoal(r,c):
            CLOSED.append((r,c))
            return l,path
        CLOSED.append((r,c))
        
        for nr,nc in start.movegen(r,c):
            if (nr,nc) not in CLOSED and all((nr,nc)!=(x[0],x[1]) for x in OPEN):
                OPEN.append((nr,nc,hewristic(nr,nc,start.n),l+1,path+[(nr,nc)]))
    return 0,"path doesnot exist"
        
grid=[[0,0,0],[0,1,0],[0,0,0]]
obj1=Grid(grid)
l,path=best_first_search(obj1)
print("length:",l)
print("path:",path)
