# BTL LTNC
<p class="has-line-data" data-line-start="0" data-line-end="1">»Hướng dẫn cài đặt</p>
<pre><code>Cài các thư viện SDL,SDL Image, SDL Mixer, SDL TTF
Linker setting các thư viện trong Codeblocks
Chạy file game.cbp để chơi
</code></pre>
<p class="has-line-data" data-line-start="6" data-line-end="7">»Mô tả chung về trò chơi, các ý tưởng chính</p>
<pre><code>Trò chơi điều khiển máy bay bắn hạ kẻ địch ( dùng các phím lên, xuống, phải, trái để di chuyển và space để bắn )
Khởi đầu với 10 mạng ( mỗi lần trúng đạn -1 mạng, va chạm địch -1 mạng )
Có 2 loại kẻ địch: địch thông thường và boss sẽ xuất hiện khi đạt 100 điểm
Khi tiêu diệt được địch thông thường sẽ được tăng điểm và có tỉ lệ 90% rơi ra vật phẩm, ăn để tăng điểm giúp boss xuất hiện nhanh hơn
Tiêu diệt boss , ăn vật phẩm khi tiêu diệt boss để tăng điểm và mạng
Nếu để kẻ địch đi qua mà không bắn hạ thì sẽ bị trừ điểm, mạng
</code></pre>
<p class="has-line-data" data-line-start="15" data-line-end="16">»Mô tả các chức năng đã cài đặt, kèm video minh họa</p>
<pre><code>Có hiệu ứng hình ảnh, âm thanh cho các loại hành động khác nhau
Hiển thị điểm, mạng người chơi
Kẻ địch xuất hiện và ra đạn ngẫu nhiên, đã giới hạn số lượng địch và đạn để có trải nghiệm chơi vừa phải nhất
Khi người chơi hết mạng, có hiệu ứng báo kết thúc trò chơi
Link youtube: 
</code></pre>
<p class="has-line-data" data-line-start="22" data-line-end="23">»Các kỹ thuật lập trình được sử dụng trong chương trình</p>
<pre><code>Thư viện SDL2.0, SDL2_image, SDL2_ttf, SDL2_mixer để render hình ảnh, âm thanh, font chữ
Dùng các chức năng cơ bản của mảng tĩnh, vector, con trỏ
Phân bố sắp xếp vị trí toạ độ các nhân vật để hợp lí
Sinh số ngẫu nhiên
Môđun hoá chương trình
</code></pre>
<p class="has-line-data" data-line-start="29" data-line-end="30">»Kết luận</p>
<pre><code>Cần chú ý trong việc phân bố các đối tượng
Ngoài việc code, cần chọn lọc hình ảnh để game có đồ hoạ đẹp 
</code></pre>
<p class="has-line-data" data-line-start="33" data-line-end="34">»Hướng phát triển</p>
<pre><code>Thêm loại đạn với đường đi chéo
Thêm chức năng tạm thời bất tử khi tiêu diệt được nhiều kẻ địch liên tiếp
Thêm chế độ tua nhanh ở màn cuối bắt làm người chơi gần như không thể sống sót qua -&gt; kết thúc trò chơi sớm
Chơi lại nhiều lần, xếp hạng điểm các lần chơi ( Do phiên bản này em để có hiệu ứng màn hình kết thúc nên không làm )
</code></pre>
<p class="has-line-data" data-line-start="39" data-line-end="40">»Các điều tâm đắc rút ra được sau khi hoàn thiện chương trình</p>
<pre><code>Nên chuẩn bị ý tưởng và lên kế hoạch cụ thể từ sớm để có thời gian cải tiến, tối ưu trò chơi 1 cách tối đa
Tham khảo từ nhiều nguồn rồi lấy những ưu điểm nhất của những nguồn đó</code></pre>
