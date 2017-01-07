function vars = create_simout_struct( logsout )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

n = logsout.numElements();

for i=1:n
    ele = logsout.getElement(i);
    
    if size(ele.Values.Data, 3) == 1
        vars.(ele.Name) = [ele.Values.Time'; ele.Values.Data'];
    else
        vars.(ele.Name) = [ele.Values.Time'; squeeze(ele.Values.Data(1, 1, :))'; squeeze(ele.Values.Data(2, 2, :))'; ];
    end
end

end

