module AoC

    @@position = 50
    @@zero_count = 0
    @@steps_list = ["Start: position = #{@@position}"]

    def self.error(msg : String) : Nil
        STDERR.puts msg
        exit 84
    end

    def self.get_password(rotations : String) : Tuple(Int32, Array(String))

        rotations.strip.split("\n").each { |line|
            direction = line[0]
            distance = line[1..-1].to_i

            case direction
            when 'L'
                @@position = (@@position - distance + 100) % 100
            when 'R'
                @@position = (@@position + distance) % 100
            else
                error("Invalid direction: #{direction}")
            end

            @@steps_list << "#{line}: position = #{@@position}"

            if @@position == 0
                @@zero_count += 1
                @@steps_list[@@steps_list.size - 1] += "  <- ZERO"
            end
        }

        return @@zero_count, @@steps_list
    end

end

if ARGV.size != 1
    AoC.error("Usage: #{File.basename(__FILE__)} <rotation>")
end

filename = ARGV[0]
content = File.read(filename) rescue AoC.error("Could not read file: #{filename}")

puts AoC.get_password(content)[0]
