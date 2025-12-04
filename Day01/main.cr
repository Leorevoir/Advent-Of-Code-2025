module AoC

    @@position = 50
    @@zero_count_p1 = 0
    @@zero_count_p2 = 0
    @@steps_list = ["Start: position = #{@@position}"]

    extend self

    def error(msg : String) : Nil
        STDERR.puts msg
        exit 84
    end

    def get_password(rotations : String) : Tuple(Int32, Int32, Array(String))

        reset()

        rotations.strip.split("\n").each { |line|
            next if line.empty?

            direction = line[0]
            distance = line[1..-1].to_i
            start = @@position

            @@zero_count_p2 += zero_hits(start, distance, direction)

            case direction
                when 'L' then rotation_l_p1(distance)
                when 'R' then rotation_r_p1(distance)
                else error("Invalid direction: #{direction}")
            end

            @@steps_list << "#{line}: position = #{@@position}"

            if @@position == 0
                @@zero_count_p1 += 1
                @@zero_count_p2 += 1
                @@steps_list[-1] += "  <- ZERO"
            end
        }

        return {@@zero_count_p1, @@zero_count_p2, @@steps_list}
    end

    private def reset() : Nil
        @@position = 50
        @@zero_count_p1 = 0
        @@zero_count_p2 = 0
        @@steps_list = ["Start: position = #{@@position}"]
    end

    private def rotation_l_p1(distance : Int32) : Nil
        @@position = (@@position - distance + 100) % 100
    end

    private def rotation_r_p1(distance : Int32) : Nil
        @@position = (@@position + distance) % 100
    end

    private def zero_hits(start : Int32, distance : Int32, direction : Char) : Int32
        return 0 if distance <= 1

        first_k =
            if direction == 'R'
                (100 - start) % 100
            else
                start % 100
            end

        first_k = 100 if first_k == 0
        return 0 if first_k > distance - 1

        remaining_distance = distance - first_k
        1 + ((distance - 1) - first_k) // 100
    end

end

if ARGV.size != 1
    AoC.error("Usage: #{File.basename(__FILE__)} <rotation>")
end

filename = ARGV[0]
content = File.read(filename) rescue AoC.error("Could not read file: #{filename}")

part1, part2, _ = AoC.get_password(content)
puts part1
puts part2
