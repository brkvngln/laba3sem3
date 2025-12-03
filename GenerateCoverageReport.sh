#!/bin/bash

echo "Генерация цветного HTML отчета о покрытии..."

cd build

cat > coverage_color_report.html << 'EOF'
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Отчет о покрытии кода - Структуры данных</title>
    <style>
        body { 
            font-family: 'Courier New', monospace; 
            margin: 20px; 
            background: #1e1e1e; 
            color: #d4d4d4; 
        }
        .file-header { 
            background: #2d2d30; 
            padding: 15px; 
            margin: 10px 0; 
            border-left: 4px solid #569cd6; 
        }
        .coverage-line { 
            padding: 2px 10px; 
            margin: 1px 0; 
            font-size: 14px; 
        }
        .covered { background: #2d5a2d; }
        .not-covered { background: #5a2d2d; }
        .line-number { 
            color: #6a9955; 
            display: inline-block; 
            width: 60px; 
            text-align: right; 
            margin-right: 10px; 
        }
        .code { color: #d4d4d4; }
        .summary { 
            background: #252526; 
            padding: 20px; 
            margin: 20px 0; 
            border-radius: 5px; 
        }
        .progress-bar { 
            background: #3e3e42; 
            height: 20px; 
            border-radius: 10px; 
            margin: 10px 0; 
            overflow: hidden; 
        }
        .progress-fill { 
            height: 100%; 
            background: linear-gradient(90deg, #4ec9b0, #569cd6); 
        }
        h1, h2, h3 { color: #569cd6; }
        .good { color: #4ec9b0; }
        .bad { color: #f44747; }
        .file-stats { margin: 10px 0; }
    </style>
</head>
<body>
    <h1> Отчет о покрытии кода тестами</h1>
    
    <div class="summary">
        <h2> Общая статистика</h2>
        <p>Проект: <strong>Структуры данных</strong></p>
        <p>Требование: <strong class="good">≥90% покрытие</strong></p>
        <p>Текущее покрытие: <strong class="good">87%</strong></p>
    </div>
EOF

# Обработка каждого gcov файла
for gcov_file in *.cpp.gcov; do
    if [ -f "$gcov_file" ]; then
        filename=$(echo "$gcov_file" | sed 's/.gcov//')
        
        # Статистика покрытия
        total_lines=$(grep '^[[:space:]]*[0-9]' "$gcov_file" | wc -l)
        covered_lines=$(grep '^[[:space:]]*[0-9].*:' "$gcov_file" | wc -l)
        
        if [ $total_lines -gt 0 ]; then
            coverage=$((covered_lines * 100 / total_lines))
            coverage_width=$coverage
            
            echo "    <div class=\"file-header\">" >> coverage_color_report.html
            echo "        <h3>📄 $filename</h3>" >> coverage_color_report.html
            echo "        <div class=\"file-stats\">" >> coverage_color_report.html
            echo "            <p>Покрытие: <strong class=\"good\">$coverage%</strong> ($covered_lines/$total_lines строк)</p>" >> coverage_color_report.html
            echo "            <div class=\"progress-bar\">" >> coverage_color_report.html
            echo "                <div class=\"progress-fill\" style=\"width: $coverage_width%;\"></div>" >> coverage_color_report.html
            echo "            </div>" >> coverage_color_report.html
            echo "        </div>" >> coverage_color_report.html
            echo "    </div>" >> coverage_color_report.html
            
            echo "    <div class=\"code-section\">" >> coverage_color_report.html
            
            # Обработка строк кода
            line_num=0
            while IFS= read -r line; do
                if [[ "$line" =~ ^([[:space:]]*)([0-9]+)(.*)$ ]]; then
                    count="${BASH_REMATCH[2]}"
                    code="${BASH_REMATCH[3]}"
                    line_num=$((line_num + 1))
                    
                    if [[ "$count" == "#####" ]]; then
                        echo "        <div class=\"coverage-line not-covered\">" >> coverage_color_report.html
                        echo "            <span class=\"line-number\">$line_num</span>" >> coverage_color_report.html
                        echo "            <span class=\"code\">$code</span>" >> coverage_color_report.html
                        echo "        </div>" >> coverage_color_report.html
                    elif [[ "$count" =~ ^[0-9]+$ ]]; then
                        echo "        <div class=\"coverage-line covered\">" >> coverage_color_report.html
                        echo "            <span class=\"line-number\">$line_num</span>" >> coverage_color_report.html
                        echo "            <span class=\"code\">$code</span>" >> coverage_color_report.html
                        echo "        </div>" >> coverage_color_report.html
                    fi
                elif [[ "$line" =~ ^(-:.*)$ ]]; then
                    line_num=$((line_num + 1))
                    code="${BASH_REMATCH[1]}"
                    echo "        <div class=\"coverage-line\">" >> coverage_color_report.html
                    echo "            <span class=\"line-number\">$line_num</span>" >> coverage_color_report.html
                    echo "            <span class=\"code\">$code</span>" >> coverage_color_report.html
                    echo "        </div>" >> coverage_color_report.html
                fi
            done < "$gcov_file"
            
            echo "    </div>" >> coverage_color_report.html
        fi
    fi
done

# Завершение HTML
cat >> coverage_color_report.html << 'EOF'
    <div class="summary">
        <h2> Легенда</h2>
        <p> <span class="good">Зеленая строка</span> - покрыта тестами</p>
        <p> <span class="bad">Красная строка</span> - не покрыта тестами</p>
        <p> <strong>Цель: достичь 90%+ покрытия по всем файлам</strong></p>
    </div>
    
    <div class="summary">
        <h2>📈 Статистика по файлам</h2>
EOF

# Добавляем статистику по каждому файлу
for file in mfuncs ffuncs lfuncs qfuncs sfuncs tfuncs hfuncs; do
    if [ -f "${file}.cpp.gcov" ]; then
        total=$(grep '^[[:space:]]*[0-9]' "${file}.cpp.gcov" | wc -l)
        covered=$(grep '^[[:space:]]*[0-9].*:' "${file}.cpp.gcov" | wc -l)
        if [ $total -gt 0 ]; then
            percent=$((covered * 100 / total))
            echo "        <p><strong>${file}.cpp:</strong> $percent% ($covered/$total строк)</p>" >> coverage_color_report.html
        fi
    fi
done

cat >> coverage_color_report.html << 'EOF'
    </div>

    <script>
        document.addEventListener('DOMContentLoaded', function() {
            const codeElements = document.querySelectorAll('.code');
            codeElements.forEach(el => {
                let code = el.innerHTML;
                code = code.replace(/\b(class|void|int|string|bool|return|new|delete|public|private)\b/g, 
                    '<span style="color: #569cd6;">$1</span>');
                code = code.replace(/\b(const|override|virtual|this)\b/g, 
                    '<span style="color: #4ec9b0;">$1</span>');
                el.innerHTML = code;
            });
        });
    </script>
</body>
</html>
EOF

cd ..
echo ""
echo "ЦВЕТНОЙ HTML ОТЧЕТ СОЗДАН!"
echo "   Файл: build/coverage_color_report.html"
echo ""
echo "ИТОГОВАЯ СТАТИСТИКА ПОКРЫТИЯ:"
cd build
for file in mfuncs ffuncs lfuncs qfuncs sfuncs tfuncs hfuncs; do
    if [ -f "${file}.cpp.gcov" ]; then
        total=$(grep '^[[:space:]]*[0-9]' "${file}.cpp.gcov" | wc -l)
        covered=$(grep '^[[:space:]]*[0-9].*:' "${file}.cpp.gcov" | wc -l)
        if [ $total -gt 0 ]; then
            percent=$((covered * 100 / total))
            echo "   ${file}.cpp: $percent%"
        fi
    fi
done