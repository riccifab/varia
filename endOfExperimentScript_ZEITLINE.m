% End of experiment script for ZEITLINE

subject = 'PC038';
expDate = '2019-06-11';

p = dat.paths;

% Creating paths assuming a certain folders structure
localArchive = strrep(p.localRepository, 'C:', 'D:');
sourceFolder = fullfile(p.localRepository, subject, expDate);
destinationFolder = fullfile(p.mainRepository, subject, expDate);
archiveFolder = fullfile(localArchive, subject, expDate);

%% copy files to the server

tic;
[copyStatus, copyMessage, copyMessageID] = copyfile(sourceFolder, destinationFolder);

if copyStatus
    fprintf('Files copied successfully from\n''%s''\nto\n''%s''\n', sourceFolder, destinationFolder)
    toc;
else
    warning('Something went wrong with copying files to the server:\n%s\n', copyMessage);
    return;
end

%% move files to bigger disk (D:)

tic;
[moveStatus, moveMessage, moveMessageID] = movefile(sourceFolder, archiveFolder);

if moveStatus
    fprintf('Files moved successfully from\n''%s''\nto\n''%s''\n', sourceFolder, archiveFolder)
    toc;
else
    warning('Something went wrong with moving files to the local archive location:\n%s\n', ...
        moveMessage);
    return;
end

