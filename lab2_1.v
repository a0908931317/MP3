`timescale 1ns/1ps
module Parameterized_Ping_Pong_Counter (
    input clk, 
    input rst_n, 
    input enable, 
    input flip, 
    input [3:0] max, 
    input [3:0] min, 
    output reg direction, 
    output reg [3:0] out
);

reg [3:0] next_out;
reg next_direction = 1;

always @(posedge clk) begin
    if(!rst_n) begin
        out <= min;
        direction <= 1;
    end
    else begin
        out <= next_out;
        direction <= next_direction;
    end
end

always @(*) begin
    if(flip == 1) begin
        if(direction == 1) next_direction = 0;
        else next_direction = 1;
    end
    else begin
        if(max == min) next_direction = direction;
        else if(out == max) next_direction = 0;
        else if(out == min) next_direction = 1;
        else next_direction = direction;
    end
end

always @(*) begin
    if(enable) begin
        if(out > max || max <= min || out < min) next_out = out;
        else begin
            if(next_direction == 1) begin
                if(out < max) next_out = out + 1;
                else next_out = out - 1;
            end
            else begin
                if(out > min) next_out = out - 1;
                else next_out = out + 1;
            end
        end
    end
    else next_out = out;
end

endmodule
