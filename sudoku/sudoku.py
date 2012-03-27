import os
#import psyco
import sys
class node:
	def __init__(self,init=0):
		self.num=init
		self.l=range(1,10)
		self.retry = 0
		
	pass

class puzzle:
	def __init__(self):
		self.p = list()
		for m in range(9):
			row = list()
			for n in range(9):
				row.append(node(m))
			self.p.append( row )
		self.cp = zip(*self.p)
		
		#function speed up
		#self.get_row = psyco.proxy(self.get_row)
		#self.get_col = psyco.proxy(self.get_col)
		#self.get_rset = psyco.proxy(self.get_rset)
		#self.get_cset = psyco.proxy(self.get_cset)
		#self.get_mset = psyco.proxy(self.get_mset)
		#self.force = psyco.proxy(self.force)



	def get_row(self,m):
		return self.p[m]

	def get_col(self,n):
		return self.cp[n]
		#return [self.p[i][n] for i in range(9)]
	
	def get_rset(self,m):
		return set( [node.num for node in p.get_row(m)] ) - set([0])

	def get_cset(self,n):
		return set( [node.num for node in p.get_col(n)] ) - set([0])

	def get_mset(self,m,n):
		mm = m-m%3
		nn = n-n%3
		l =list()
		for row in p.p[mm:mm+3]:
			for node in row[nn:nn+3]:
				l.append(node.num) 
		return set(l) - set([0])
			
	def set_row(self,row,str):
		for i,node in enumerate(row):
			if str[i] == ".":
			    node.num = 0
			else:
				node.num = int(str[i])
			
	def set(self,grid):
		for m,row in enumerate(self.p):
			input = grid[m*9:(m+1)*9]
			self.set_row(row, input)

	def show_nodelist(self,nodelist,show=0):
		for i,node in enumerate(nodelist):
			if node.num == 0 and show:
					print node.l,
			else:
				print node.num,
			if i==2 or i==5:
				print "|",
		print ""
			
	def show(self,show=0):
		print "====================="
		for i,row in enumerate(self.p):
			self.show_nodelist(row)
			if i==2 or i==5:
				print "---------------------"
		print "====================="

			
	def strip(self):
		mnnodelist = list();
		for m,row in enumerate(self.p):
			rset=set([n.num for n in row]) - set([0])
			for n,node in enumerate(row):
				if node.num == 0:
					cset = set([self.p[i][n].num for i in range(9) ])- set([0])
					mset = self.get_mset(m, n)
					node.l=list(set(range(1,10))-rset-cset-mset)
					if len(node.l) == 1:
						node.num = node.l.pop()
					else:
					   mnnodelist.append( [(m,n),node ] )
				else:
					node.l = list()
			#end for
		#end for
		return mnnodelist			
			
	def force(self):
		#get xlist
		xlist=self.strip()
		
		#sort xlist by len(node.l)
		xlist.sort( key=(lambda x:len(x[1].l)) )

		i=0;j=0;
		end=len(xlist)
		while i< end:
			#sys.stdout.write("\r")
			#sys.stdout.write( "%010d,%sl" %(j,"".join(["- " for c in xrange(i)])) )
			j+=1
			(m,n),node = xlist[i]
			usage = set(node.l) -  self.get_rset(m) - self.get_cset(n) - self.get_mset(m,n)
			if len(usage) == 0 or node.retry == len(usage):
				if node.retry == len(usage):
					#too many error, go back again
					node.retry = 0
				#end if
				i -= 1
				(m,n),node = xlist[i]
				node.l.append(node.num)
				node.num=0
			else:
				for x in node.l:
					if x in usage:
						node.retry += 1
						node.num=x
						node.l.remove(x)
						break
				i=i+1
			#end else
		print ""
		print j

		
grid = \
'''
..1...5..
...273...
4.......6
.8..9..1.
.5.1.2.7.
.4..8..3.
9.......7
...614...
..6...4..
'''

#grid = \
#'''3...8.......7....51..............36...2..4....7...........6.13..452...........8..'''
#grid = \
#'''85...24..72......9..4.........1.7..23.5...9...4...........8..7..17..........36.4.'''
#grid = \
#'''..9.....3.....9...7.....5.6..65..4.....3......28......3..75.6..6...........12.3.8'''
grid=grid.replace("\n", "").replace(" ", "")
p=puzzle()
p.set(grid)
p.show()

xlist=p.strip()
p.show()

# sort xlist 
xlist.sort( key=(lambda x:len(x[1].l)) )

for l in xlist:
	print len(l[1].l),
else:
	print ""
   
p.force()
p.show()	



		
