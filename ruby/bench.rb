#!/usr/bin/ruby


require_relative "hll.rb"


class Benchmark
	def initialize(p,n)
		@p = p
                @n = n
        end

        def go() 
                hll = Hll.new(@p)
                debut = Time.now
                for x in 0..@n.to_i do
                    hll.AddItem(x)
                end
                print hll.Count()
                print "\n"
                fin = Time.now
                duree = fin-debut
                print "temps = "+duree.to_s+"ms \n";
        end
end

print ARGV[0];
bencheur = Benchmark.new(14, ARGV[0])
bencheur.go();
