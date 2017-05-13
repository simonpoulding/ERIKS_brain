function getIP()
   tmr.alarm (1, 500, 1, function()
      if wifi.sta.getip() == nil then
         print (".")
      else        
         tmr.stop(1)
         print (""..wifi.sta.getip())
      end
   end)
end

function con(SSID, PWD)
    wifi.setmode(wifi.STATION)
    wifi.sta.config(SSID,PWD)
    wifi.sta.connect()
end

function setIP(_IP,_MASK,_GW)
   wifi.sta.setip({ip=_IP,netmask=_MASK,gateway=_GW})
end

function getFeed(_host,_path,_params,_options)
   
    conn=net.createConnection(net.TCP, 0) 

    conn:on("connection", function(conn, payload) 
                       conn:send("GET ".._path.._params
                        .." HTTP/1.1\r\n" 
                        .."Host: ".._host.."\r\n" 
                        .."Connection: close\r\n"
                        .."Accept: */*\r\n" 
                        .."User-Agent: Mozilla/4.0 "
                        .."(compatible; Piccolino by wctek.com;)"
                        .."\r\n\r\n")
                       end) 
    
    conn:connect(8000,_host) 
    conn:on("receive", function(conn, payload)
    local feed=payload

    print(feed);
    
    conn:close()
    end) 

end
