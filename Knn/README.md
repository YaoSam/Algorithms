#KNN�㷨�Ľ�ʵ��

##����˼·
KNN���ʾ��ǶԼ��ϵ�һ�����֡�ֻ�ǻ��ֵĽ粢��ȷ����  
���������ƣ�����������������������ʵ���ϱ�����Ҫ�򵥣���Ϊ����õ����������ϵ���ʱû�б�Ҫ�ġ�  
���ǵ�KNN�㷨���ǲο�������뷨������ͨ���򻯵�����������õ�ǰk��Ԫ�ء�  
����ͨ����ϲ�ͬ���㷨�Ӷ��õ�һ��ƽ�����ܽϺõ�KNN�㷨��

---------

##�㷨˵��

### �㷨1 ������-ά��ǰk������
ɨ��һ���n-k��Ԫ�ء�ά��ǰk�����е����ֵ����Ȼ��ɨ����󣬺���n-k������ǰ��k��Ԫ��Ҫ��
������Ż��Ĺؼ������������ٵ�ά�����ֵ��  
- ��򵥵�������ÿ�ζ�����ǰ���Ԫ�صõ����ֵ����Ȼ����ȡ��   
 - ���Ӷ�O(n*k)  
- �ڶ��������Ƕ�ǰ���Ԫ������(�Ӵ�С)��������һ��Ԫ�ؾ������ֵ��ÿ��ҲֻҪ���Ƚ�Ԫ�ز��뵽��Ӧλ�ü��ɡ���������Ϊ�򻯰�Ĳ�������������Ȼ�ӿ������ֵ�Ĳ��ҡ����ӵĻ�����ά��ǰK��Ԫ�ص�����ʵ��KNN��˵Ҳ��û��Ҫ�ġ�  
 - ���Ӷ�O(n)~O(n*k)  
-  ����������������ǰkԪ�ؽ������ѡ��׸�Ԫ��Ҳ�����ֵ��      
ÿ���滻��Ҳֻ��Ҫ�ڴ��ϵ���ά���Ѽ��ɡ����Կ����򻯰�Ķ����򡣹�������Ϊ����ʽknn��      


- **���Ӷ�**��O(n)~O(n\*log(k))  
- **�ŵ�**��k��СʱЧ�ʺܸߡ�������k=1ʱ��ΪO(n)��  
- **ȱ��**��  
 - k�ϴ�ʱЧ�ʽϵ͡�
 - ���ȶ������ݲ�̫�õ�ʱ�������˻���O(n*log(k))�������


### �㷨2 ����-ͨ�����ϻ��֣�
���ѡȡһ��Ԫ�ض�������л��֡��ٶ�k���ڵ�һ�߽��л��֡����Ͻ���ֱ���պ÷ֳ�ǰk��Ԫ�ء�  
��������Ϊ�򻯰�Ŀ��ţ��൱��ֻ���п��ŵ�һ����֧����  
��������Ϊ����ʽknn��  
����ֻ��Ҫ����һ����֧�Ļ��֡�����û���õݹ�ʵ�֡�ֱ������ѭ����
- **���Ӷ�**��O(n)~O(n^2)��  
- **�ŵ�**��	��Խ�Ϊ�ȶ�������Ч����kӰ����١���k�ϴ��ʱ��Ч����Խϸߣ�  
- **ȱ��**��	
 - Ч����kӰ����١���k��С��ʱ��Ч����Խϵͣ�  
 - ��Բ��õ����ݻ��˻���ð�����򡭡�O(n^2)���� 


### 2.3	�㷨3 Introspective KNN ��

�����ǰ�������㷨�ġ�ȡ��������  
�ڿ���ʽknn�ĵݹ���뵽һ����Ȼ���k���n��С�������ת��Ϊ����ʽknn��  
����ֹ����ʽknn�˻���O(n^2)��Ҳ��ֹ�˶���ʽknn����k�Ƚϴ������������ݱȽϲ��õ������  
�Ӷ��õ�һ��**ƽ�����ܽϺ�**���㷨��

��ʵ���������ǲο���C++��������sort��ʵ�֡�  
�ο���<http://www.udpwork.com/item/12284.html>