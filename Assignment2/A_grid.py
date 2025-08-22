class Grid:
    def __init__(self,start):
        self.start=start
        self.n=len(start)
        
    def testgoal(self,r,c):
        return r==self.n-1 and c==self.n-1
    
    def movegen(self,r,c):
        directions=[(0,1),(0,-1),(1,0),(-1,0),(-1,-1),(1,1),(-1,1),(1,-1)]
        moves=[]
        for i,j in directions:
            ni,nj=r+i,c+j
            if 0<=ni<self.n and 0<=nj<self.n and self.start[ni][nj]==0:
                moves.append((ni,nj))
        return moves 
    
def hewristic(r,c,n):
    return max(abs(n-1-r), abs(n-1-c))

def A_star(obj):
    start=(0,0)
    goal=(obj.n-1,obj.n-1)
    
    if obj.start[0][0] != 0 or obj.start[goal[0]][goal[1]] != 0:
        return "infinity","path does not exist"
    
    OPEN=[(hewristic(0,0,obj.n),1,start,[start])]
    CLOSED=set()
    
    while OPEN:
        N=min(OPEN,key=lambda x:x[0])
        OPEN.remove(N)
        f,g,(r,c),path=N
        
        if obj.testgoal(r,c):
            return g,path
        
        if (r,c) in CLOSED:
            continue
        CLOSED.add((r,c))
        
        for nr,nc in obj.movegen(r,c):
            new_g = g + 1
            h = hewristic(nr,nc,obj.n)
            new_f = new_g + h
            OPEN.append((new_f,new_g,(nr,nc), path + [(nr,nc)]))
    
    return "infinity","path does not exist"

grid=[[0,0,0],[0,1,0],[0,0,0]]
obj1=Grid(grid)
l,path=A_star(obj1)
print("length:",l)
print("path:",path)
