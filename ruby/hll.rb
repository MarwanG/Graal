#!/usr/bin/ruby

class Hll
    
    def initialize(p)
       @b = p;
       @buckets = Array.new
       @m = 2**@b
       for i in 0..@m
           @buckets << 0
       end
    end


    def alpha(m)
        if m == 16 then
            return 0.673;
        elsif m == 32 then
            return 0.697
        elsif m == 64 then
            return 0.709
        else
          return 0.7213/(1+ 1.079/m)
        end
    end


    def AddItem(n)
        # on met un 1 au 32eme bit pour que les entiers soient tous de la meme longueur
        #n = (n & (2**(32) -1)) + 2**32
        #numero du bucket 
        j = n >> (32 - @b)
        #j = j - 2**self.b
        # reste
        w = n & 2**(32 - @b) -1
        w = w + 2**(32 - @b)
        #r = self.rho(w)
        r = 0
        @buckets[j] = [@buckets[j], r].max
      end



    def Count() 
        sum = 0;
        #calcul de la moyenne harmonique
        for i in 0..@buckets.length do 
            nb = @buckets[i]
            denum = 2**nb.to_i
            sum += 1/denum
        end
        sum = 1.0/sum;
        e =  self.alpha(@m)*(@m**2)*sum;

        if(e < 5.0/2*@m) then  # linear counting
            v = 0; 
            for i in 0..@m do
                if (@buckets[i] == 0) then
                    v+=1;
                end
            end
            if(v != 0) then 
                e = @m * Math.log(@m/v)
            end
        end
        if(e > 1.0/30*2**32) then  # correction
            e = -2**32*Math.log(@m/2**32)
        end
        return e;
        end 


    def rho(val) # calcul de la position du premier bit a 0 de val
        val = val & 2**(32 - @b)-1
        rho = (33 - @b) - val.bit_length()
        return rho 
    end



end

test = Hll.new(14)
test.AddItem(0)
test.Count()
